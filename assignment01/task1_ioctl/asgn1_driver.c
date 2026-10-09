#define pr_fmt(fmt)    "asgn1_driver: " fmt
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/string.h>
#include <linux/errno.h>
#include "asgn1_ioctl.h"

#define DRIVER_NAME    "asgn1_driver"
#define DEVICE_NAME    "asgn1"
#define BUF_SIZE       4096
#define KERNEL_PREFIX  "[KERNEL] "
#define DRIVER_VERSION "asgn1_driver v1.0 - SE203437"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("STUDENT");
MODULE_DESCRIPTION("ASGN1 char driver with ioctl support");

static int major_num = 241;
module_param(major_num, int, 0444);
MODULE_PARM_DESC(major_num, "Major number (241-254)");

static DEFINE_MUTEX(asgn1_lock);
static char dev_buf[BUF_SIZE];
static int  buf_len;
static int  open_count;
static int  write_count;
static int  read_count;
static int  last_write_size;
static int  mode = ASGN1_MODE_ECHO;

static int asgn1_open(struct inode *inode, struct file *filp)
{
    mutex_lock(&asgn1_lock);
    open_count++;
    pr_info("open() called, open_count=%d\n", open_count);
    mutex_unlock(&asgn1_lock);
    return 0;
}

static int asgn1_release(struct inode *inode, struct file *filp)
{
    pr_info("release() called\n");
    return 0;
}

static ssize_t asgn1_read(struct file *filp, char __user *ubuf,
                          size_t count, loff_t *ppos)
{
    size_t n;
    ssize_t ret = 0;

    mutex_lock(&asgn1_lock);

    if (*ppos == 0)
        read_count++;

    if (*ppos >= buf_len)
        goto out;
    n = min(count, (size_t)(buf_len - *ppos));
    if (copy_to_user(ubuf, dev_buf + *ppos, n)) {
        ret = -EFAULT;
        goto out;
    }
    *ppos += n;
    ret = n;
out:
    mutex_unlock(&asgn1_lock);
    return ret;
}

static ssize_t asgn1_write(struct file *filp, const char __user *ubuf,
                           size_t count, loff_t *ppos)
{
    size_t prefix_len, n;
    ssize_t ret;

    mutex_lock(&asgn1_lock);

    prefix_len = (mode == ASGN1_MODE_KERNEL) ? strlen(KERNEL_PREFIX) : 0;
    n = min(count, (size_t)(BUF_SIZE - prefix_len));

    memcpy(dev_buf, KERNEL_PREFIX, prefix_len);
    if (copy_from_user(dev_buf + prefix_len, ubuf, n)) {
        buf_len = 0;
        dev_buf[0] = '\0';
        ret = -EFAULT;
        goto out;
    }

    buf_len = prefix_len + n;
    write_count++;
    last_write_size = n;
    pr_info("write() %zu bytes, mode=%d, buf_len=%d\n", n, mode, buf_len);
    ret = n;
out:
    mutex_unlock(&asgn1_lock);
    return ret;
}

static long asgn1_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    struct asgn1_stats st;
    char ver[ASGN1_VERSION_LEN];
    int new_mode;

    if (_IOC_TYPE(cmd) != ASGN1_IOC_MAGIC)
        return -ENOTTY;

    switch (cmd) {
    case ASGN1_RESET_BUFFER:
        pr_info("ioctl ASGN1_RESET_BUFFER called\n");
        mutex_lock(&asgn1_lock);
        buf_len = 0;
        dev_buf[0] = '\0';
        write_count = 0;
        read_count = 0;
        last_write_size = 0;
        mutex_unlock(&asgn1_lock);
        break;

    case ASGN1_GET_STATS:
        pr_info("ioctl ASGN1_GET_STATS called\n");
        mutex_lock(&asgn1_lock);
        st.open_count       = open_count;
        st.write_count      = write_count;
        st.read_count       = read_count;
        st.buffer_len       = buf_len;
        st.last_write_size  = last_write_size;
        st.mode             = mode;
        mutex_unlock(&asgn1_lock);

        if (copy_to_user(argp, &st, sizeof(st)))
            return -EFAULT;
        break;

    case ASGN1_SET_MODE:
        pr_info("ioctl ASGN1_SET_MODE called\n");
        if (copy_from_user(&new_mode, argp, sizeof(new_mode)))
            return -EFAULT;
        if (new_mode != ASGN1_MODE_KERNEL && new_mode != ASGN1_MODE_ECHO)
            return -EINVAL;

        mutex_lock(&asgn1_lock);
        mode = new_mode;
        mutex_unlock(&asgn1_lock);
        pr_info("mode changed to %d (%s)\n", new_mode,
                new_mode == ASGN1_MODE_KERNEL ? "KERNEL" : "ECHO");
        break;

    case ASGN1_GET_VERSION:
        pr_info("ioctl ASGN1_GET_VERSION called\n");
        memset(ver, 0, sizeof(ver));
        strscpy(ver, DRIVER_VERSION, sizeof(ver));
        if (copy_to_user(argp, ver, sizeof(ver)))
            return -EFAULT;
        break;

    default:
        pr_info("unknown ioctl cmd 0x%x\n", cmd);
        return -ENOTTY;
    }

    return 0;
}

static const struct file_operations asgn1_fops = {
    .owner          = THIS_MODULE,
    .open           = asgn1_open,
    .release        = asgn1_release,
    .read           = asgn1_read,
    .write          = asgn1_write,
    .unlocked_ioctl = asgn1_ioctl,
};

static int __init asgn1_init(void)
{
    int ret;

    if (major_num < 241 || major_num > 254) {
        pr_err("major_num=%d out of range (241-254)\n", major_num);
        return -EINVAL;
    }

    ret = register_chrdev(major_num, DEVICE_NAME, &asgn1_fops);
    if (ret < 0) {
        pr_err("register_chrdev failed: %d\n", ret);
        return ret;
    }

    pr_info("loaded, major=%d, default mode=ECHO. Tao node: mknod /dev/%s c %d 0\n",
            major_num, DEVICE_NAME, major_num);
    return 0;
}

static void __exit asgn1_exit(void)
{
    unregister_chrdev(major_num, DEVICE_NAME);
    pr_info("unloaded, cleanup done\n");
}

module_init(asgn1_init);
module_exit(asgn1_exit);