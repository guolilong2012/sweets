#include <linux/module.h>
#include <linux/fs.h>
#include <asm-generic/uaccess.h>

#define MY_FILE "/root/test/kernel_file/test.conf"

static int kernel_file(void)
{
    int i;
    loff_t fsize = 0;
    struct file *file = NULL;
    mm_segment_t old_fs;
    char *buf = NULL;

    file = filp_open(MY_FILE, O_RDWR|O_CREAT, 0644);
    if (!file || IS_ERR(file))
    {
        printk("Open file <%s> failed!\n", MY_FILE);
        return -1;
    }

    fsize = file->f_dentry->d_inode->i_size;
    printk(KERN_ALERT"size = %d\n", (int)fsize);

    buf = (char *)kmalloc(fsize, GFP_ATOMIC);
    if (!buf)
    {
        printk("kmalloc error!\n");
        goto CLOSE_FILE;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    vfs_read(file, buf, fsize, &file->f_pos);
    for (i = 0; i < fsize; i++)
    {
        printk("%c", buf[i]);
    }
    printk("\n");
    vfs_write(file, "Write OK!\n", 10, &file->f_pos);
    set_fs(old_fs);

    filp_close(file, current->files);

    return 0;

CLOSE_FILE:
    filp_close(file, current->files);
    return -1;
}

static int file_init(void)
{
    if (kernel_file() < 0)
    {
        printk("kernel read/write file failed!\n");
        return -1;
    }

    printk("Init OK!\n");

    return 0;
}

void file_exit(void)
{
    printk("Exit OK!\n");
}

module_init(file_init);
module_exit(file_exit);

MODULE_LICENSE("Dual BSP/GPL");
MODULE_AUTHOR("Guo");
MODULE_DESCRIPTION("");
MODULE_VERSION("");
MODULE_ALIAS("");
