#include <linux/init.h>   // Driver initialization methods
#include <linux/module.h> // Module macros, structures and functions
#include <linux/types.h>  // Types such as dev_t
#include <linux/cdev.h>   // Prepare the character device
#include <linux/fs.h>	  // File system utilities
#include <linux/kdev_t.h> // Major and minor number information

#include "defines.h" // General macros
#include "fops/ldp_fops.h" // Custom file operations

#define MINOR_VERSION_START 0
#define MINOR_VERSION_AMOUNT 1

// License, author and description
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Caio Marcelo Campoy Guedes <caiomcg@gmail.com>");
MODULE_DESCRIPTION("Test driver, use for learning purpose only");

struct linux_driver_playground {
	struct semaphore* sem;
    struct cdev* my_cdev;
	dev_t dev_num;
} ldp;

void cleanup(struct linux_driver_playground* pldp) {
	unregister_chrdev_region(pldp->dev_num, MINOR_VERSION_AMOUNT);

	if (pldp->my_cdev != NULL) {
		cdev_del(pldp->my_cdev);
	}

	// if (pldp->sem != NULL) {
	// 	(void)
	// }
}

static int __init ldp_init(void) {
	int status_code = 0;

    printk(KERN_INFO "%s: Loaded", MODULE_NAME);

	// Ask the kernel to allocate the a major number for the device, use the default minor version
	// of 0 as we do not need extra communitcation.
	if ((status_code = alloc_chrdev_region(&(ldp.dev_num), MINOR_VERSION_START, MINOR_VERSION_AMOUNT, MODULE_NAME)) < 0) {
		printk(KERN_ALERT "%s: could not register character device\n", MODULE_NAME);
		goto fail;
	}

	// Initialize a character device structure with the desired file operations and initialize
	// its attributes
	if ((ldp.my_cdev = cdev_alloc()) == NULL) {
		goto fail;
	}

	(ldp.my_cdev)->ops   = &ldp_fops;
	(ldp.my_cdev)->owner = THIS_MODULE;

	// Add the character device to the kernel table
	if ((status_code = cdev_add(ldp.my_cdev, ldp.dev_num, MINOR_VERSION_AMOUNT)) < 0) {
		goto fail;
	}

	printk(KERN_INFO "%s: is open with major number %d\n", MODULE_NAME, MAJOR(ldp.dev_num));

	return 0;

fail:
	cleanup(&ldp);

    return status_code;
}

static void __exit ldp_exit(void) {
    printk(KERN_INFO "%s: Unloaded\n", MODULE_NAME);
	cleanup(&ldp);
}

module_init(ldp_init);
module_exit(ldp_exit);
