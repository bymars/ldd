/*
 * Written on 2013.12.11
 * First code with parameter
 * Liu, Linhong
 */

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int howmany = 1;
static char *whom = "WORLD";

module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static int hello_init(void)
{
	int i;
	for (i = 0; i < howmany; i++) {
		printk(KERN_ALERT "HELLO %s\n", whom);
	}
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "GOODBYE WORLD\n");
}

module_init(hello_init);
module_exit(hello_exit);
