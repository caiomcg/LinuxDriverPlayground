#include "ldp_fops.h"
#include "../defines.h"

int cmedia_open(struct inode* inode, struct file* filp) {
	printk(KERN_INFO "%s: Trying to open cmedia sound card [NOT IMPLEMENTED]", MODULE_NAME);
	return 0;
}

int cmedia_release(struct inode* inode, struct file* filp) {
	printk(KERN_INFO "%s: Releasing cmedia sound card [NOT IMPLEMENTED]", MODULE_NAME);
	return 0;
}
