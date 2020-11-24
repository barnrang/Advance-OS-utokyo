#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#define PRINT_PREF "[INTERRUPT_TEST]:"

irqreturn_t handler(int irq, void *data)
{
    printk(PRINT_PREF "Enter handler\n");
    return IRQ_HANDLED;
}

static int __init interrupt_init(void)
{
    unsigned int irq = 2;
    printk(PRINT_PREF "Enter Initialization\n");
    int status = request_irq(irq, handler, 0, "test-handler", NULL);
    printk(PRINT_PREF "handler added\n");
    // Trigger IRQ 
    asm("int $50");
    return 0;
}

static void __exit interrupt_exit(void)
{
    unsigned int irq = 2;
    printk(PRINT_PREF "Exiting module\n");
    free_irq(irq,NULL); 

}

module_init(interrupt_init);
module_exit(interrupt_exit);

MODULE_LICENSE("GPL");
