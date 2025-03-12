#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led, *button;

#define IO_LED 21
#define IO_BUTTON 20

static int __init my_init(void)
{
	/* Request the LED GPIO */
	led = gpiod_get_optional(NULL, "gpio21", GPIOD_OUT_LOW);
	if (IS_ERR(led)) {
		printk("gpioctrl - Error getting GPIO %d\n", IO_LED);
		return PTR_ERR(led);
	}

	/* Request the Button GPIO */
	button = gpiod_get_optional(NULL, "gpio20", GPIOD_IN);
	if (IS_ERR(button)) {
		printk("gpioctrl - Error getting GPIO %d\n", IO_BUTTON);
		gpiod_put(led);  // Release LED GPIO before returning
		return PTR_ERR(button);
	}

	/* Set LED to HIGH */
	gpiod_set_value(led, 1);

	printk("gpioctrl - Button is %spressed\n", gpiod_get_value(button) ? "" : "not ");

	return 0;
}

static void __exit my_exit(void)
{
	printk("gpioctrl - Unloading driver\n");

	/* Turn off LED */
	gpiod_set_value(led, 0);

	/* Release GPIOs */
	gpiod_put(led);
	gpiod_put(button);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("An example for using GPIOs with gpiod");
