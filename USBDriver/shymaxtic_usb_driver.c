#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/slab.h>
#include "shymaxtic_device.h"

#define D_VENDOR_ID         0x1ea7
#define D_PRODUCT_ID        0x0064
#define D_DEVICE_NAME       "Shymaxtic USB"


int i = 0;
int ret = 0;
int maijor_number = 0;
struct shymaxtic_device_t *shymaxtic_dev = NULL;
// Initialize usb_device_id
static struct usb_device_id g_id_table[] = {
    {USB_DEVICE(D_VENDOR_ID, D_PRODUCT_ID)},
    {},
};
// Allow user-space know which device this driver control.
MODULE_DEVICE_TABLE(usb, g_id_table);
/******************************************************************/

/* .probe callback */
static int shymaxitc_usb_driver_probe(struct usb_interface* usb_if, const struct usb_device_id* id) {
    // Get information of the usb device.
    struct usb_host_interface* usb_host_if = NULL;
    struct usb_endpoint_descriptor* endpoint = NULL;
    struct usb_device *udev = NULL;
    usb_host_if = usb_if->cur_altsetting;
    dev_info(&usb_if->dev, 
            "Pen i/f %d now probed: (%04X:%04X)\n", 
            usb_host_if->desc.bInterfaceNumber,
            id->idVendor, id->idProduct);
    dev_info(&usb_if->dev, 
            "ID->bNumEndpoints: %02X\n",
            usb_host_if->desc.bNumEndpoints);
    dev_info(&usb_if->dev, 
             "ID->bInterfaceClass: %02X\n",
            usb_host_if->desc.bInterfaceClass);
    for (i = 0; i < usb_host_if->desc.bNumEndpoints; ++i) {
        endpoint = &usb_host_if->endpoint[i].desc;
        dev_info(&usb_if->dev, 
                "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, endpoint->bEndpointAddress);
        dev_info(&usb_if->dev, 
                "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);
        dev_info(&usb_if->dev, 
               "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize,
                endpoint->wMaxPacketSize);
    }            

    // Prepare my usb struct.        
    udev = interface_to_usbdev(usb_if);

    // Increments the reference count of the usb device structure
    shymaxtic_dev->udev = usb_get_dev(udev);

    // Save our data pointer in this usb_if device.
    usb_set_intfdata(usb_if, shymaxtic_dev);
    dev_info(&usb_if->dev, "Shymaxtic USB attached\n");
    return 0;
}

/* .disconnect callback */
static void shymaxtic_usb_driver_disconnect(struct usb_interface* usb_if) {
    shymaxtic_dev = usb_get_intfdata(usb_if);
    usb_set_intfdata(usb_if, NULL);

    // release a use of the usb device structure
    usb_put_dev(shymaxtic_dev->udev);
    dev_info(&usb_if->dev, "Shymaxtic USB disconnected\n");
}

// Prepare usb driver
static struct usb_driver shymaxtic_usb_driver = {
    .name = "Shymaxtic USB",
    .probe = shymaxitc_usb_driver_probe,
    .disconnect = shymaxtic_usb_driver_disconnect,
    .id_table = g_id_table,
};

/********************************************************************************/
// function for modprobe module.
static int __init shymaxtic_usb_driver_init(void) {
    printk(KERN_INFO "Init moudle\n");
    ret = usb_register(&shymaxtic_usb_driver);
    if (ret < 0) {
        printk(KERN_ERR "Shymaxtic USB: Cannot register usb\n");
    }

    // Allocate memory in kernel for our device.
    shymaxtic_dev = kzalloc(sizeof(struct shymaxtic_device_t), GFP_KERNEL);
    if (shymaxtic_dev == NULL) {
        printk(KERN_ERR "Faile to allocate shymaxtic device\n");
        return -ENOMEM;
    }

    // Registry major, minor number
    ret = alloc_chrdev_region(&shymaxtic_dev->dev_num, 0, 1, D_DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate a major number\n");
        return ret;
    }

    // Add to /sys/class
    shymaxtic_dev->cl = class_create(THIS_MODULE, "shymaxticdrv");
    if (shymaxtic_dev->cl == NULL) {
        unregister_chrdev_region(shymaxtic_dev->dev_num, 1);
        return PTR_ERR(shymaxtic_dev->cl);
    }

    // Add to /dev
    if (device_create(shymaxtic_dev->cl, NULL, shymaxtic_dev->dev_num, NULL, "shymaxticdevice") == NULL) {
        class_destroy(shymaxtic_dev->cl);
        unregister_chrdev_region(shymaxtic_dev->dev_num, 1);
        return PTR_ERR(NULL);
    }

    // Allocate cdev
    shymaxtic_dev->cdev = cdev_alloc();
    if (shymaxtic_dev->cdev == NULL) {
        printk(KERN_ERR "Failed to allocate cdev\n");
        return PTR_ERR(shymaxtic_dev->cdev);
    }
    cdev_init(shymaxtic_dev->cdev, &fops);

    // Registry cdev with VFS
    ret = cdev_add(shymaxtic_dev->cdev, shymaxtic_dev->dev_num, 1); 
    if (ret < 0) {
        device_destroy(shymaxtic_dev->cl, shymaxtic_dev->dev_num);
        class_destroy(shymaxtic_dev->cl);
        unregister_chrdev_region(shymaxtic_dev->dev_num, 1);
        return ret;
    }
    return 0;
}
// function for rmmod module.
static void __exit shymaxtic_usb_driver_exit(void) {
    usb_deregister(&shymaxtic_usb_driver);
    cdev_del(shymaxtic_dev->cdev);
    device_destroy(shymaxtic_dev->cl, shymaxtic_dev->dev_num);
    class_destroy(shymaxtic_dev->cl);
    unregister_chrdev_region(shymaxtic_dev->dev_num, 1);
    kfree(shymaxtic_dev);
    printk(KERN_INFO "Unloaded module\n");
}

module_init(shymaxtic_usb_driver_init);
module_exit(shymaxtic_usb_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shymaxtic");
MODULE_DESCRIPTION("Shymaxtic USB driver");