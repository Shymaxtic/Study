#include "shymaxtic_device.h"
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>

#define D_DEVICE_NAME       "Shymaxtic USB"

 struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = shymaxtic_device_open,
    .release = shymaxtic_device_close
};

int shymaxtic_device_open(struct inode* inode, struct file* filep) {
    // TODO
    return 0;
}

int shymaxtic_device_close(struct inode* inode, struct file* filep) {
    // TODO
    return 0;
}

int shymaxtic_device_init(struct shymaxtic_device_t** gdevp) {
    int ret = 0;
    struct shymaxtic_device_t* gdev = NULL;
    // Allocate memory in kernel for our device.
    *gdevp = kzalloc(sizeof(struct shymaxtic_device_t), GFP_KERNEL);
    gdev = *gdevp;
    if (gdev == NULL) {
        printk(KERN_ERR "Faile to allocate shymaxtic device\n");
        return -ENOMEM;
    }

    // Registry major, minor number
    ret = alloc_chrdev_region(&gdev->dev_num, 0, 1, D_DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate a major number\n");
        return ret;
    }

    // Add to /sys/class
    gdev->cl = class_create(THIS_MODULE, "shymaxticdrv");
    if (gdev->cl == NULL) {
        unregister_chrdev_region(gdev->dev_num, 1);
        return PTR_ERR(gdev->cl);
    }

    // Add to /dev
    if (device_create(gdev->cl, NULL, gdev->dev_num, NULL, "shymaxticdevice") == NULL) {
        class_destroy(gdev->cl);
        unregister_chrdev_region(gdev->dev_num, 1);
        return PTR_ERR(NULL);
    }

    // Allocate cdev
    gdev->cdev = cdev_alloc();
    if (gdev->cdev == NULL) {
        printk(KERN_ERR "Failed to allocate cdev\n");
        return PTR_ERR(gdev->cdev);
    }
    cdev_init(gdev->cdev, &fops);

    // Registry cdev with VFS
    ret = cdev_add(gdev->cdev, gdev->dev_num, 1); 
    if (ret < 0) {
        device_destroy(gdev->cl, gdev->dev_num);
        class_destroy(gdev->cl);
        unregister_chrdev_region(gdev->dev_num, 1);
        return ret;
    }
    return 0;
}

void shymaxtic_device_deinit(struct shymaxtic_device_t* gdev) {
    if (gdev == NULL) {
        printk(KERN_WARNING "Null device");
        return;
    }
    cdev_del(gdev->cdev);
    device_destroy(gdev->cl, gdev->dev_num);
    class_destroy(gdev->cl);
    unregister_chrdev_region(gdev->dev_num, 1);
    kfree(gdev);
}