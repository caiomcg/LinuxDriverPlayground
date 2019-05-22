#ifndef FOPS_LDP_FOPS_H
#define FOPS_LDP_FOPS_H

#include <linux/fs.h> // File system utilities

int cmedia_open(struct inode* inode, struct file* filp);
int cmedia_release(struct inode* inode, struct file* filp);

#endif
