#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define DEVICE_NAME "asgn1"
#define ASGN1_RESET_BUFFER _IO('a', 1)
struct asgn1_stats {
    int open_count;
    int write_count;
    int read_count;
    int buffer_len;
    int last_write_size;
};
#define ASGN1_GET_STATS _IOR('a', 2, struct asgn1_stats)

static int major_number;

static char device_buffer[1024];
static size_t buffer_size = 0;
static unsigned int write_count = 0;
static unsigned int read_count = 0;
static unsigned int open_count = 0;
static unsigned int last_write_size = 0;

static int a_open(struct inode *inode, struct file *file)
{
    open_count++;
    printk(KERN_INFO "Assignment 1 open\n");
    return 0;
}

static int a_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Assignment 1 closed\n");
    return 0;
}

static ssize_t a_read(
    struct file *file,
    char __user *buffer,
    size_t len,
    loff_t *offset)
{
    size_t bytes_to_read;

    if (*offset >= buffer_size)
        return 0;

    bytes_to_read = buffer_size - *offset;

    if (len < bytes_to_read)
        bytes_to_read = len;

    if (copy_to_user(buffer,
                     device_buffer + *offset,
                     bytes_to_read))
        return -EFAULT;

    *offset += bytes_to_read;
    read_count++;

    return bytes_to_read;
}

static ssize_t a_write(
    struct file *file,
    const char __user *buffer,
    size_t len,
    loff_t *offset)
{
    size_t bytes_to_write;

    bytes_to_write = len;

    if (bytes_to_write > sizeof(device_buffer))
        bytes_to_write = sizeof(device_buffer);

    if (copy_from_user(device_buffer,
                       buffer,
                       bytes_to_write))
        return -EFAULT;

    buffer_size = bytes_to_write;
    write_count++;
    last_write_size = bytes_to_write;
    printk(KERN_INFO "Received %zu bytes\n",
           bytes_to_write);

    return bytes_to_write;
}
static long a_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    switch(cmd){
        case ASGN1_RESET_BUFFER:
            buffer_size = 0;
            write_count = 0;
            read_count = 0;
            last_write_size = 0;
            printk(KERN_INFO "Buffer and counter reset\n");
            return 0;
        case ASGN1_GET_STATS:
{
    struct asgn1_stats stats;

    stats.open_count = open_count;
    stats.write_count = write_count;
    stats.read_count = read_count;
    stats.buffer_len = buffer_size;
    stats.last_write_size = last_write_size;

    if (copy_to_user(
            (struct asgn1_stats __user *)arg,
            &stats,
            sizeof(stats)))
        return -EFAULT;

    return 0;
}
    default:
        return -EINVAL;
    }
}
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = a_open,
    .read = a_read,
    .write = a_write,
    .unlocked_ioctl = a_ioctl,
    .release = a_release,
};

static int __init a_init(void)
{
    major_number = register_chrdev(
        0,
        DEVICE_NAME,
        &fops
    );

    if (major_number < 0) {
        printk(KERN_ALERT "failed to register device\n");
        return major_number;
    }

    printk(KERN_INFO
           "registered with major number %d\n",
           major_number);

    return 0;
}

static void __exit a_exit(void)
{
    unregister_chrdev(
        major_number,
        DEVICE_NAME
    );

    printk(KERN_INFO "driver unloaded\n");
}

module_init(a_init);
module_exit(a_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SE203437");
MODULE_DESCRIPTION("Basic Linux Character Device Driver");
MODULE_VERSION("1.0");
