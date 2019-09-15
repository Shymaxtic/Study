#ifndef SHYMAXTIC_DEVICE_H
#define SHYMAXTIC_DEVICE_H

#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/usb.h>

// My data struct .
struct shymaxtic_device_t {
    struct usb_device   *udev;
    struct cdev         *cdev; 
    // char name[128];
    // char data[128];
    // struct semaphore sem;    
    dev_t   dev_num;  
    struct class *cl; 
};

// File operation callbacks.
int shymaxtic_device_open(struct inode* inode, struct file* filep);
int shymaxtic_device_close(struct inode* inode, struct file* filep);

// Registry callbacks
extern struct file_operations fops;

#endif