#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/slab.h>
#define PRINT_PREF "[KMALLOC_TEST]:"

static int __init student_id_init(void)
{
    char *std_id;
    const char std_to_copy[9] = "48296128";

    printk(PRINT_PREF "Entering module.\n");

    std_id = kmalloc(sizeof(char) * 9, GFP_KERNEL);
    if (!std_id)
    {
        printk("Error");
    }
    else
    {
        int i;
		for(i = 0; i < 8; i++)
		{
            std_id[i] = std_to_copy[i];
		}
        std_id[i] = '\0';
        printk("My student Id %s", std_id);
        kfree(std_id);
    }

    return 0;

}

static void __exit student_id_exit(void)
{
    printk(KERN_INFO "Exiting module.\n");
}

module_init(student_id_init);
module_exit(student_id_exit);

MODULE_LICENSE("GPL");
