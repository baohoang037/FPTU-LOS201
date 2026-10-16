#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define DEVICE_NAME "counter"

// Các biến thống kê và đếm bảo vệ bằng atomic_t để an toàn đa tiến trình (SMP)
static atomic_t counter_val = ATOMIC_INIT(0);
static atomic_t read_count = ATOMIC_INIT(0);
static atomic_t write_count = ATOMIC_INIT(0);

// Hàm xử lý READ: Trả về giá trị counter, auto-increment và xử lý ppos tránh lặp vô hạn
static ssize_t counter_read(struct file *file, char __user *buf, size_t len, loff_t *ppos) {
    char kbuf[32];
    int val, ret_len;

    // Nếu ppos > 0 nghĩa là đã đọc rồi, trả về 0 để báo kết thúc (tránh cat lặp vô hạn)
    if (*ppos > 0)
        return 0;

    // Lấy giá trị hiện tại và tăng counter lên 1 (auto-increment on read)
    val = atomic_read(&counter_val);
    atomic_inc(&counter_val);
    atomic_inc(&read_count);

    // Chuyển giá trị thành chuỗi ASCII kết thúc bằng newline
    ret_len = snprintf(kbuf, sizeof(kbuf), "%d\n", val);

    if (len < ret_len)
        return -EINVAL;

    if (copy_to_user(buf, kbuf, ret_len))
        return -EFAULT;

    *ppos += ret_len; // Cập nhật con trỏ file offset
    return ret_len;
}

// Hàm xử lý WRITE: Nhận số nguyên từ userspace, set counter hoặc reset về 0
static ssize_t counter_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos) {
    char kbuf[32];
    int new_val, ret;

    if (len >= sizeof(kbuf))
        return -EINVAL;

    if (copy_from_user(kbuf, buf, len))
        return -EFAULT;

    kbuf[len] = '\0';

    // Parse chuỗi thành số nguyên sử dụng kstrtoint
    ret = kstrtoint(strim(kbuf), 10, &new_val);
    if (ret < 0 || new_val < 0) {
        return -EINVAL; // Trả về lỗi nếu không phải số hoặc số âm
    }

    atomic_set(&counter_val, new_val);
    atomic_inc(&write_count);

    return len;
}

// Hàm hiển thị thông tin khi đọc file /proc/counter_info
static int counter_proc_show(struct seq_file *m, void *v) {
    seq_printf(m, "Current Counter Value: %d\n", atomic_read(&counter_val));
    seq_printf(m, "Total Reads (Increments): %d\n", atomic_read(&read_count));
    seq_printf(m, "Total Writes (Resets/Sets): %d\n", atomic_read(&write_count));
    return 0;
}

static int counter_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, counter_proc_show, NULL);
}

static const struct proc_ops counter_proc_ops = {
    .proc_open = counter_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

// Cấu trúc file_operations cho misc device
static const struct file_operations counter_fops = {
    .owner = THIS_MODULE,
    .read = counter_read,
    .write = counter_write,
};

// Đăng ký misc device với major số 10 cố định
static struct miscdevice counter_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &counter_fops,
};

static int __init counter_init(void) {
    int ret = misc_register(&counter_misc_device);
    if (ret) {
        pr_err("counter: Failed to register misc device\n");
        return ret;
    }

    // Tạo file proc /proc/counter_info
    proc_create("counter_info", 0444, NULL, &counter_proc_ops);
    pr_info("counter: Driver loaded successfully (/dev/counter)\n");
    return 0;
}

static void __exit counter_exit(void) {
    remove_proc_entry("counter_info", NULL);
    misc_deregister(&counter_misc_device);
    pr_info("counter: Driver unloaded\n");
}

module_init(counter_init);
module_exit(counter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SinhVien - MSSV");
MODULE_DESCRIPTION("A simple counter misc device driver");
