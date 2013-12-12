/*
 * First char device driver scull
 * Written on 2013.12.12
 *
 * Liu, Linhong
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/cdev.h> // Macro MKDEV use this
#include <linux/fs.h> // register_chrdev...

#include "scull.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liu, Linhong");

int scull_major = SCULL_MAJOR;
int scull_minor = 0;
int scull_nr_devs = SCULL_NR_DEVS;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);

loff_t scull_llseek(struct file *filp, loff_t off, int whence)
{
	return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos)
{
	return count;
}

ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos)
{
	return count;
}

long scull_ioctl(struct inode *inode, struct file *filp,
		unsigned int cmd, unsigned long arg)
{
	return 0;
}

int scull_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "%s\n", __func__);
	return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "%s\n", __func__);
	return 0;
}

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_llseek,
	.read = scull_read,
	.write = scull_write,
	.unlocked_ioctl = scull_ioctl,
	.open = scull_open,
	.release = scull_release,
};

static int scull_init_module(void) 
{
	int result;
	dev_t dev = 0;
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_nr_devs, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
			"scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_ALERT "scull: can't get major %d\n", scull_major);
		return result;
	}
	printk(KERN_ALERT "%s: register char dev number major %d\n", __func__, scull_major);
	return 0;
}

static void scull_cleanup_module(void) 
{
	dev_t dev = MKDEV(scull_major, scull_minor);
	unregister_chrdev_region(dev, scull_nr_devs);
	printk(KERN_ALERT "%s:unregister char dev number major %d\n", __func__, scull_major);
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);
//module_cleanup(scull_cleanup);

