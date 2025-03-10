#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void);
static void my_exit(void);

static int my_init(void)
{
	printk("hello - Hello, Kernel!\n");
	return 0;
}

static void __exit my_exit(void)
{
	printk("hello man - Goodbye man, Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Rateliff");
MODULE_DESCRIPTION("A simple Hello WOrld Linux Kernel Module");