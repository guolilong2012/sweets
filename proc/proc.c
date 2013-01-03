#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>

unsigned int debug = 0;
struct proc_dir_entry *g_proc_dir = NULL;
struct proc_dir_entry *g_proc_file = NULL;

static int my_read_proc(char *page, char **start, off_t offset, int count, int *eof,
                     void *data)
{
    int len = 0;

    printk("proc read\n");

    if (offset > 0)
    {
        *eof = 1;
        return 0;
    }

    len = sprintf(page, "debug %u\n", *(unsigned int *)data);

    return len;
}

static int my_write_proc(struct file *file, const char __user *buffer, unsigned long count,
                      void *data)
{
    char tmp[50];

    printk("proc write\n");

    if (copy_from_user(tmp, buffer, sizeof(tmp)))
    {
        return -1;
    }

    sscanf(tmp, "%u", (unsigned int *)data);

    return sizeof(unsigned int);
}

static int proc_init(void)
{
    printk("Proc Init\n");

    g_proc_dir = proc_mkdir("guo", NULL);
    if (!g_proc_dir)
    {
        printk("Proc mkdir failed\n");
        return -1;
    }

    g_proc_file = create_proc_entry("information", 0644, g_proc_dir);
    if (!g_proc_file)
    {
        remove_proc_entry("guo", NULL);
        printk("Proc create entry failed\n");
        return -1;
    }
    g_proc_file->data = (void *)&debug;
    g_proc_file->write_proc = my_write_proc;
    g_proc_file->read_proc = my_read_proc;

    debug = 250;

    return 0;
}

static void proc_exit(void)
{
    printk("Proc Exit!\n");
    remove_proc_entry("information", g_proc_dir);
    remove_proc_entry("guo", NULL);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("Dual BSP/GPL");
MODULE_AUTHOR("Guo Lilong");

