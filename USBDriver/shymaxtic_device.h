#ifndef SHYMAXTIC_DEVICE_H
#define SHYMAXTIC_DEVICE_H

#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/usb.h>

// My device .
struct shymaxtic_device_t {
    struct usb_device       *udev;
    struct cdev             *cdev; 
    char                    name[128];
    char                    data[128];
    struct semaphore        sem;    
    dev_t                   dev_num;  
    struct class            *cl; 
};

// My file
struct shymaxtic_device_file_t {
    struct shymaxtic_device_t* dev;    
};


// File operation callbacks.
static int shymaxtic_device_open(struct inode* inode, struct file* filep);
static int shymaxtic_device_close(struct inode* inode, struct file* filep);
static long shymaxtic_device_ioctl(struct file* filep, unsigned int cmd, unsigned long arg__);
static ssize_t shymaxtic_device_read(struct file *f, char __user *buf, size_t len, loff_t *off);
static ssize_t shymaxtic_device_write(struct file *f, const char __user *buf, size_t len, loff_t *off);

extern struct file_operations fops;
extern struct shymaxtic_device_t *shymaxtic_dev;

int shymaxtic_device_init(struct shymaxtic_device_t** gdev);
void shymaxtic_device_deinit(struct shymaxtic_device_t* gdev);

#endif