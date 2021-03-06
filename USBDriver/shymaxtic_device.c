#include "shymaxtic_device.h"
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/uaccess.h>
#include "shymaxtic_device_file_ioctl.h"

#define D_DEVICE_NAME       "Shymaxtic USB"


 struct file_operations shymaxtic_fops = {
    .owner = THIS_MODULE,
    .open = shymaxtic_device_open,
    .release = shymaxtic_device_close,
    .read = shymaxtic_device_read,
    .write = shymaxtic_device_write,
    .unlocked_ioctl = shymaxtic_device_ioctl
};

struct shymaxtic_device_t *shymaxtic_dev = NULL;

static int shymaxtic_device_open(struct inode* inode, struct file* filep) {
    int ret = 0;
    // Allocate device file
    struct shymaxtic_device_file_t* shymaxtic_file = NULL;
    shymaxtic_file = (struct shymaxtic_device_file_t*)kzalloc(sizeof(struct shymaxtic_device_file_t), GFP_KERNEL);
    if (shymaxtic_file == NULL) {
        printk(KERN_ERR "Failed to allocate device file\n");
        return -ENOMEM;
    }
    shymaxtic_file->dev = shymaxtic_dev;
    filep->private_data = shymaxtic_file;
    if (shymaxtic_dev->udev == NULL) {
        printk(KERN_WARNING "USB device not present\n");
        return -ENOMEM;
    }
    // Do task
    ret = usb_get_descriptor(shymaxtic_dev->udev, USB_DT_STRING, 0, shymaxtic_dev->name, 128);
    if (ret < 0) {
        return ret;
    }
    printk(KERN_INFO "%s", shymaxtic_dev->name);
    printk(KERN_INFO "Opened file");
    return 0;
}

static int shymaxtic_device_close(struct inode* inode, struct file* filep) {
    // Deallocate device file
    struct shymaxtic_device_file_t* shymaxtic_file = NULL;
    shymaxtic_file = (struct shymaxtic_device_file_t*)filep->private_data;
    if (shymaxtic_file == NULL) {
        printk(KERN_WARNING "Device file not allocated yet\n");
        return -ENOMEM;
    }
    kfree(shymaxtic_file);
    printk(KERN_INFO "Closed file");
    return 0;
}

static long shymaxtic_device_ioctl(struct file* filep, unsigned int cmd, unsigned long arg__) {
    struct shymaxtic_device_file_t* shymaxtic_file = NULL;
    int result = 0;
    struct shymaxtic_device_t* shymaxtic_dev = NULL;
    struct usb_device* udev = NULL;
    int pipeOut = 0;
    int actualLen = 0;
    shymaxtic_file = (struct shymaxtic_device_file_t* )filep->private_data;
    if (shymaxtic_file == NULL) {
        printk(KERN_WARNING "Device file not allocated yet\n");
        return -ENOMEM;
    }
    shymaxtic_dev = shymaxtic_file->dev;
    if (shymaxtic_dev == NULL) {
        printk(KERN_WARNING "Device not allocated yet\n");
        return -ENOMEM;
    }
    udev = shymaxtic_dev->udev;
    if (udev == NULL) {
        printk(KERN_WARNING "Usb device not allocated yet\n");
        return -ENOMEM;
    }
    switch (cmd)
    {
    case IOCTL_SHYMAXTIC_PING: {
        pipeOut = usb_sndbulkpipe(udev, 0);
        result = usb_bulk_msg(udev, pipeOut, 'Q', 1, &actualLen, 10000);
        if (result != 0) {
            printk(KERN_ERR "Cannot send data to device USB\n");
        }
        printk(KERN_WARNING "IOCTL_SHYMAXTIC_PING");
    }        
        break;
    case IOCTL_SHYMAXTIC_GET_BAUDRATE: {
        // Cast arg_ to address of user space varialbe
        uint64_t __user *user_params = (int64_t*)arg__;
        // Get data in kernel space.
        uint64_t baudrate = 0;
        if (unlikely(user_params == NULL)) {
            result = -EINVAL;
            break;
        }
        // TODO: get baudrate from device.
        if (result == 0) {
            // Put from kernel space to user space.
            put_user(baudrate, user_params);
        }
    }
        break;
    default:
        break;
    }
    return result;
}

static ssize_t shymaxtic_device_read(struct file *f, char __user *buf, size_t len, loff_t *off) {
    // TODO
    printk(KERN_INFO "Read file\n");
    return 0;
}

static ssize_t shymaxtic_device_write(struct file *filep, const char __user *buf, size_t len, loff_t *off) {
    // TODO
    return 0;
}


int shymaxtic_device_init(struct shymaxtic_device_t** gdevp) {
    int ret = 0;
    struct device* dev_ret = NULL;
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
    if (IS_ERR(gdev->cl)) {
        unregister_chrdev_region(gdev->dev_num, 1);
        return PTR_ERR(gdev->cl);
    }

    // Add to /dev
    dev_ret = device_create(gdev->cl, NULL, gdev->dev_num, NULL, "shymaxticdevice");
    if (IS_ERR(dev_ret)) {
        class_destroy(gdev->cl);
        unregister_chrdev_region(gdev->dev_num, 1);
        return PTR_ERR(dev_ret);
    }

    // Allocate cdev
    gdev->cdev = cdev_alloc();
    if (IS_ERR(gdev->cdev)) {
        printk(KERN_ERR "Failed to allocate cdev\n");
        return PTR_ERR(gdev->cdev);
    }
    cdev_init(gdev->cdev, &shymaxtic_fops);

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