#ifndef FOPS_LDP_FOPS_H
#define FOPS_LDP_FOPS_H

#include <linux/fs.h>      // File system utilities
#include <linux/usb.h>     // USB operations
#include <linux/types.h>   // Types such as dev_t
#include <linux/cdev.h>    // Prepare the character device
#include <linux/module.h>  // Module macros, structures and functions

int cmedia_open(struct inode* inode, struct file* filp);
int cmedia_release(struct inode* inode, struct file* filp);
long cmedia_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);

int cmedia_probe(struct usb_interface* intf, const struct usb_device_id* id);
void cmedia_diconnect(struct usb_interface* intf);

struct linux_driver_playground {
	struct semaphore sem;
    struct cdev* my_cdev;
	dev_t dev_num;
};

extern struct usb_driver ldp_usb_driver;
extern struct linux_driver_playground ldp;
extern struct file_operations ldp_fops;

#endif
