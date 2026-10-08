/**
 * @file sms_sensor_driver.c
 * @brief Simulated Temperature & Humidity Sensor Character Device Driver
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/random.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/version.h>
#include <linux/mutex.h>

#include "sms_sensor.h"

#define CLASS_NAME "sms_sensor_class"
#define BUFFER_SIZE 128

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Ngoc Gia Bao");
MODULE_DESCRIPTION("Simulated Temperature and Humidity Sensor Driver for Assignment 02");
MODULE_VERSION("1.0");

static dev_t dev_number;
static struct cdev sms_cdev;
static struct class *sms_class = NULL;
static struct device *sms_device = NULL;
static struct proc_dir_entry *proc_entry = NULL;

/* Driver statistics and state */
static uint32_t g_min_interval_ms = MIN_INTERVAL_MS;
static uint64_t g_read_count = 0;
static uint64_t g_last_read_ms = 0;
static uint64_t g_driver_start_time_sec = 0;

static int g_last_temp_scaled = 2500;  /* 25.00 °C */
static int g_last_humid_scaled = 5000; /* 50.00 % */

static DEFINE_MUTEX(sensor_lock);

/* Helper to get time in milliseconds */
static inline uint64_t get_current_time_ms(void)
{
    return (uint64_t)ktime_to_ms(ktime_get());
}

/* File operations: open */
static int sms_open(struct inode *inodep, struct file *filep)
{
    return 0;
}

/* File operations: release */
static int sms_release(struct inode *inodep, struct file *filep)
{
    return 0;
}

/* File operations: read */
static ssize_t sms_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
    char kbuf[BUFFER_SIZE];
    int str_len;
    uint64_t current_time_ms;
    uint32_t rand_t, rand_h;

    /* Prevent repeated reads during a single open session (EOF handling) */
    if (*offset > 0)
        return 0;

    if (mutex_lock_interruptible(&sensor_lock))
        return -ERESTARTSYS;

    current_time_ms = get_current_time_ms();

    /* Enforce minimum sampling interval */
    if (g_last_read_ms > 0 && (current_time_ms - g_last_read_ms) < g_min_interval_ms) {
        mutex_unlock(&sensor_lock);
        return -EAGAIN;
    }

    /* Simulate temperature: 15.00 - 45.00 °C (scaled by 100) */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0)
    rand_t = get_random_u32();
    rand_h = get_random_u32();
#else
    rand_t = prandom_u32();
    rand_h = prandom_u32();
#endif

    g_last_temp_scaled = 1500 + (rand_t % 3001);
    g_last_humid_scaled = 3000 + (rand_h % 6001);

    g_last_read_ms = current_time_ms;
    g_read_count++;

    str_len = snprintf(kbuf, sizeof(kbuf), "%llu,%d.%02d,%d.%02d\n",
                       current_time_ms,
                       g_last_temp_scaled / 100, g_last_temp_scaled % 100,
                       g_last_humid_scaled / 100, g_last_humid_scaled % 100);

    mutex_unlock(&sensor_lock);

    if (len < str_len)
        return -EINVAL;

    if (copy_to_user(buffer, kbuf, str_len))
        return -EFAULT;

    *offset += str_len;
    return str_len;
}

/* File operations: unlocked_ioctl */
static long sms_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    uint32_t new_interval;

    switch (cmd) {
    case SMS_SET_INTERVAL:
        if (copy_from_user(&new_interval, (uint32_t __user *)arg, sizeof(new_interval)))
            return -EFAULT;

        if (new_interval < 50 || new_interval > 5000)
            return -EINVAL;

        mutex_lock(&sensor_lock);
        g_min_interval_ms = new_interval;
        mutex_unlock(&sensor_lock);
        pr_info("sms_sensor: interval updated to %u ms\n", new_interval);
        break;
    default:
        return -ENOTTY;
    }

    return 0;
}

/* Procfs: read /proc/sms_stats */
static ssize_t sms_proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    char kbuf[256];
    int len;
    uint64_t uptime_sec;

    if (*ppos > 0)
        return 0;

    uptime_sec = (uint64_t)ktime_get_seconds() - g_driver_start_time_sec;

    mutex_lock(&sensor_lock);
    len = snprintf(kbuf, sizeof(kbuf),
                   "read_count: %llu\n"
                   "last_temperature: %d.%02d\n"
                   "last_humidity: %d.%02d\n"
                   "driver_uptime_sec: %llu\n"
                   "min_interval_ms: %u\n",
                   g_read_count,
                   g_last_temp_scaled / 100, g_last_temp_scaled % 100,
                   g_last_humid_scaled / 100, g_last_humid_scaled % 100,
                   uptime_sec,
                   g_min_interval_ms);
    mutex_unlock(&sensor_lock);

    if (count < len)
        return -EINVAL;

    if (copy_to_user(buf, kbuf, len))
        return -EFAULT;

    *ppos += len;
    return len;
}

static const struct file_operations sms_fops = {
    .owner = THIS_MODULE,
    .open = sms_open,
    .release = sms_release,
    .read = sms_read,
    .unlocked_ioctl = sms_ioctl,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static const struct proc_ops sms_proc_ops = {
    .proc_read = sms_proc_read,
};
#else
static const struct file_operations sms_proc_ops = {
    .read = sms_proc_read,
};
#endif

/* Module entry point */
static int __init sms_driver_init(void)
{
    int ret;

    g_driver_start_time_sec = (uint64_t)ktime_get_seconds();

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("sms_sensor: failed to allocate char dev region\n");
        return ret;
    }

    cdev_init(&sms_cdev, &sms_fops);
    sms_cdev.owner = THIS_MODULE;

    ret = cdev_add(&sms_cdev, dev_number, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_number, 1);
        pr_err("sms_sensor: failed to add cdev\n");
        return ret;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    sms_class = class_create(CLASS_NAME);
#else
    sms_class = class_create(THIS_MODULE, CLASS_NAME);
#endif
    if (IS_ERR(sms_class)) {
        cdev_del(&sms_cdev);
        unregister_chrdev_region(dev_number, 1);
        pr_err("sms_sensor: failed to create device class\n");
        return PTR_ERR(sms_class);
    }

    sms_device = device_create(sms_class, NULL, dev_number, NULL, DEVICE_NAME);
    if (IS_ERR(sms_device)) {
        class_destroy(sms_class);
        cdev_del(&sms_cdev);
        unregister_chrdev_region(dev_number, 1);
        pr_err("sms_sensor: failed to create device\n");
        return PTR_ERR(sms_device);
    }

    proc_entry = proc_create(PROC_FILENAME, 0444, NULL, &sms_proc_ops);
    if (!proc_entry) {
        device_destroy(sms_class, dev_number);
        class_destroy(sms_class);
        cdev_del(&sms_cdev);
        unregister_chrdev_region(dev_number, 1);
        pr_err("sms_sensor: failed to create /proc/%s\n", PROC_FILENAME);
        return -ENOMEM;
    }

    pr_info("sms_sensor: driver loaded successfully, /dev/%s and /proc/%s created\n",
            DEVICE_NAME, PROC_FILENAME);
    return 0;
}

/* Module exit point */
static void __exit sms_driver_exit(void)
{
    if (proc_entry)
        remove_proc_entry(PROC_FILENAME, NULL);

    if (sms_device)
        device_destroy(sms_class, dev_number);

    if (sms_class)
        class_destroy(sms_class);

    cdev_del(&sms_cdev);
    unregister_chrdev_region(dev_number, 1);

    pr_info("sms_sensor: driver unloaded successfully\n");
}

module_init(sms_driver_init);
module_exit(sms_driver_exit);
