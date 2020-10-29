#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/gfp.h>
#include<linux/highmem.h>
#define PRINT_PREF "[HIGHMEM__TEST]:"

static int __init student_id_init(void)
{
    struct page *my_page;
    char *std_id;
    const char std_to_copy[9] = "48296128";
    int i;

    printk(PRINT_PREF "Entering module.\n");

    my_page = alloc_page(GFP_HIGHUSER);
    if (!my_page)
    {
        printk(PRINT_PREF "Cannot allocate page\n");
        return -1;
    }
    std_id = kmap(my_page);
    for(i = 0; i < 8; i++)
    {
        std_id[i] = std_to_copy[i];
    }
    std_id[i] = '\0';
    printk(PRINT_PREF "My student Id %s", std_id);

    kunmap(my_page);
    __free_pages(my_page, 0);

    return 0;

}

static void __exit student_id_exit(void)
{
    printk(KERN_INFO "Exiting module.\n");
}

module_init(student_id_init);
module_exit(student_id_exit);

MODULE_LICENSE("GPL");
