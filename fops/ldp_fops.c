#include "ldp_fops.h"

#include <linux/sched.h>
#include <asm/uaccess.h>

#include "../constants.h"

struct linux_driver_playground ldp = {
	.my_cdev = NULL,
	.dev_num = 0,
};

/* table of devices that work with this driver */
static struct usb_device_id ldp_table[] = {
	{USB_DEVICE(LDP_USB_VENDOR, LDP_USB_PRODUCT)},
	{}
	/* Terminating entry */
};

MODULE_DEVICE_TABLE(usb, ldp_table);

int cmedia_open(struct inode *inode, struct file *filp) {
	if (down_interruptible(&ldp.sem) != 0) {
		printk(KERN_ALERT "%s: could not lock the device during open", MODULE_NAME);
		return -1;
	}

	printk(KERN_INFO "%s: Trying to open cmedia sound card [NOT IMPLEMENTED]", MODULE_NAME);
	return 0;
}

int cmedia_release(struct inode *inode, struct file *filp) {
	up(&ldp.sem);
	printk(KERN_INFO "%s: Releasing cmedia sound card [NOT IMPLEMENTED]", MODULE_NAME);
	return 0;
}

long cmedia_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	int err = 0;
	long retval = 0;
	int set_val = 0;

	/*
	* extract the type and number bitfields, and don't decode
	* wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok( )
	*/
	if (_IOC_TYPE(cmd) != LDP_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > LDP_IOC_MAXNR)
		return -ENOTTY;

	/**
	 * access_ok is part of asm/uaccess
	 * this method can be used to verify if the data is valid for reading or writing.
	 * Rememver to always use it to tranfer the data from user space to kernel space.
	 */
	if (_IOC_DIR(cmd) & _IOC_READ) {
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	} else if (_IOC_DIR(cmd) & _IOC_WRITE) {
		err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	}

	// If the value is not good to be read or written to, then it is faulty
	if (err)
		return -EFAULT;

	switch (cmd) {
	case LDP_IOCRESET:
		printk(KERN_INFO "%s: Performing ioctl LDP_IOCRESET [NOT IMPLEMENTED]", MODULE_NAME);
		break;
	case LDP_IOGDEPTH:
		retval = __put_user(0x18, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOGDEPTH [NOT IMPLEMENTED]", MODULE_NAME);
		break;
	case LDP_IOGRATE:
		retval = __put_user(0xBB80, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOGRATE [NOT IMPLEMENTED]", MODULE_NAME);
		break;
	case LDP_IOGCHANNELS:
		retval = __put_user(0x02, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOGCHANNELS [NOT IMPLEMENTED]", MODULE_NAME);
		break;
	case LDP_IOSDEPTH:
		// Only sysadmins should be able to set information
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(set_val, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOSDEPTH (%d) [NOT IMPLEMENTED]", MODULE_NAME, set_val);
		break;
	case LDP_IOSRATE:
		// Only sysadmins should be able to set information
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(set_val, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOSRATE (%d) [[NOT IMPLEMENTED]", MODULE_NAME, set_val);
		break;
	case LDP_IOSCHANNELS:
		// Only sysadmins should be able to set information
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(set_val, (int __user *)arg);
		printk(KERN_INFO "%s: Performing ioctl LDP_IOSCHANNELS (%d) [[NOT IMPLEMENTED]", MODULE_NAME, set_val);
		break;
	default:
		printk(KERN_INFO "%s: Performing ioctl UNSUPORTED VALUE [NOT IMPLEMENTED]", MODULE_NAME);
		return -ENOTTY;
	}
	return retval;
}

int cmedia_probe(struct usb_interface *intf, const struct usb_device_id *id) {
	printk(KERN_INFO "%s: May have a valid card [NOT IMPLEMENTED]", MODULE_NAME);
	return 0;
}
void cmedia_diconnect(struct usb_interface *intf) {
	printk(KERN_INFO "%s: Releasing the card [NOT IMPLEMENTED]", MODULE_NAME);
}

struct usb_driver ldp_usb_driver = {
	.name = MODULE_NAME,
	.id_table = ldp_table,
	.probe = cmedia_probe,
	.disconnect = cmedia_diconnect,
};

struct file_operations ldp_fops = {
	.owner = THIS_MODULE,
	.open = cmedia_open,
	.release = cmedia_release,
	.unlocked_ioctl = cmedia_ioctl,
};
