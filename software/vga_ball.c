#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "vga_ball.h"

#define DRIVER_NAME "vga_ball"

/* Device Registers */
#define MESSAGE_TYPE(x) (x)
#define TIMESTAMP(x) ((x)+1)
#define ORDER_REF_NUMBER(x) ((x)+2)
#define TRANS_ID(x) ((x)+3)
#define ORDER_BOOK_ID(x) ((x)+4)
#define SIDE(x) ((x)+5)
#define QTY(x) ((x)+6)
#define PRICE(x) ((x)+7)
#define YIELD(x) ((x)+8)
#define BUFFER_NOT_EMPTY(x) ((x)+9)
#define READPORTT(x) ((x)+10)

/*
 * Information about our device
 */
struct vga_ball_dev {
	struct resource res;
	void __iomem *virtbase;
	vga_ball_color_t message;
} dev;

/*
 * Write segments of a single digit
 * Assumes digit is in range and the device information has been set up
 */
static void write_data(vga_ball_color_t *message)
{
	iowrite8(message->msg_type, MESSAGE_TYPE(dev.virtbase) );
	iowrite8(message->timestamp, TIMESTAMP(dev.virtbase) );
	iowrite8(message->order_ref_number, ORDER_REF_NUMBER(dev.virtbase) );
	iowrite8(message->trans_id, TRANS_ID(dev.virtbase) );
	iowrite8(message->order_book_id, ORDER_BOOK_ID(dev.virtbase) );
	iowrite8(message->side, SIDE(dev.virtbase) );
	iowrite8(message->qty, QTY(dev.virtbase) );
	iowrite8(message->price, PRICE(dev.virtbase) );
	iowrite8(message->yield, YIELD(dev.virtbase) );
	iowrite8(1, BUFFER_NOT_EMPTY(dev.virtbase));
	dev.message = *message;
}


/*
 * Handle ioctl() calls from userspace:
 * Read or write the segments on single digits.
 * Note extensive error checking of arguments
 */
static long vga_ball_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	vga_ball_arg_t vla;
	switch (cmd) {
	case VGA_BALL_WRITE_DATA:
		if (copy_from_user(&vla, (vga_ball_arg_t *) arg,
				sizeof(vga_ball_arg_t)))
			return -EACCES;
		write_data(&vla.message);
		break;
	
	case VGA_BALL_READ_DATA:
		vla.message = dev.message;
		if (copy_to_user((vga_ball_arg_t *) arg, &vla,
				sizeof(vga_ball_arg_t)))
			return -EACCES;
		break;
	default:
		return -EINVAL;
	}
	
	return 0;
}

/* The operations our device knows how to do */
static const struct file_operations vga_ball_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = vga_ball_ioctl,
};

/* Information about our device for the "misc" framework -- like a char dev */
static struct miscdevice vga_ball_misc_device = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= DRIVER_NAME,
	.fops		= &vga_ball_fops,
};

/*
 * Initialization code: get resources (registers) and display
 * a welcome message
 */
static int __init vga_ball_probe(struct platform_device *pdev)
{
        vga_ball_color_t message = { 0x410000000000000000000003ea00000000000500cd4200000001000000000000000100000000 };
	int ret;

	/* Register ourselves as a misc device: creates /dev/vga_ball */
	ret = misc_register(&vga_ball_misc_device);

	/* Get the address of our registers from the device tree */
	ret = of_address_to_resource(pdev->dev.of_node, 0, &dev.res);
	if (ret) {
		ret = -ENOENT;
		goto out_deregister;
	}

	/* Make sure we can use these registers */
	if (request_mem_region(dev.res.start, resource_size(&dev.res),
			       DRIVER_NAME) == NULL) {
		ret = -EBUSY;
		goto out_deregister;
	}

	/* Arrange access to our registers */
	dev.virtbase = of_iomap(pdev->dev.of_node, 0);
	if (dev.virtbase == NULL) {
		ret = -ENOMEM;
		goto out_release_mem_region;
	}
        
	/* Set an message */
        write_data(&message);

	return 0;

out_release_mem_region:
	release_mem_region(dev.res.start, resource_size(&dev.res));
out_deregister:
	misc_deregister(&vga_ball_misc_device);
	return ret;
}

/* Clean-up code: release resources */
static int vga_ball_remove(struct platform_device *pdev)
{
	iounmap(dev.virtbase);
	release_mem_region(dev.res.start, resource_size(&dev.res));
	misc_deregister(&vga_ball_misc_device);
	return 0;
}

/* Which "compatible" string(s) to search for in the Device Tree */
#ifdef CONFIG_OF
static const struct of_device_id vga_ball_of_match[] = {
	{ .compatible = "csee4840,vga_ball-1.0" },
	{},
};
MODULE_DEVICE_TABLE(of, vga_ball_of_match);
#endif

/* Information for registering ourselves as a "platform" driver */
static struct platform_driver vga_ball_driver = {
	.driver	= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(vga_ball_of_match),
	},
	.remove	= __exit_p(vga_ball_remove),
};

/* Called when the module is loaded: set things up */
static int __init vga_ball_init(void)
{
	pr_info(DRIVER_NAME ": init\n");
	return platform_driver_probe(&vga_ball_driver, vga_ball_probe);
}

/* Calball when the module is unloaded: release resources */
static void __exit vga_ball_exit(void)
{
	platform_driver_unregister(&vga_ball_driver);
	pr_info(DRIVER_NAME ": exit\n");
}

module_init(vga_ball_init);
module_exit(vga_ball_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HFT Book Builder Team, Columbia University");
MODULE_DESCRIPTION("VGA ball driver");