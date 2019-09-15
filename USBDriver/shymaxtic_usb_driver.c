#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/slab.h>

#define D_VENDOR_ID         0x1ea7
#define D_PRODUCT_ID        0x0064

// Initialize usb_device_id
static struct usb_device_id g_id_table[] = {
    {USB_DEVICE(D_VENDOR_ID, D_PRODUCT_ID)},
    {},
};
// Allow user-space know which device this driver control.
MODULE_DEVICE_TABLE(usb, g_id_table);
/******************************************************************/

// My data struct .
struct shymaxtic_usb_driver_t {
    struct usb_device *udev;
};

/* .probe callback */
static int shymaxitc_usb_driver_probe(struct usb_interface* usb_if, const struct usb_device_id* id) {
    // Get information of the usb device.
    struct usb_host_interface* usb_host_if = NULL;
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
    struct usb_endpoint_descriptor* endpoint = NULL;
    int i;
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
    struct usb_device *udev = interface_to_usbdev(usb_if);
    struct shymaxtic_usb_driver_t * gdev = NULL;
    // Allocate memory in kernel for our device.
    gdev = kzalloc(sizeof(*gdev), GFP_KERNEL);
    if (gdev == NULL) {
        dev_err(&usb_if->dev, "Out of memory\n");
        return -ENOMEM;
    }
    // Increments the reference count of the usb device structure
    gdev->udev = usb_get_dev(udev);
    // Save our data pointer in this usb_if device.
    usb_set_intfdata(usb_if, gdev);
    dev_info(&usb_if->dev, "Shymaxtic USB attached\n");
    return 0;
}

/* .disconnect callback */
static void shymaxtic_usb_driver_disconnect(struct usb_interface* usb_if) {
    struct shymaxtic_usb_driver_t
    *gdev = NULL;
    gdev = usb_get_intfdata(usb_if);
    usb_set_intfdata(usb_if, NULL);
    // release a use of the usb device structure
    usb_put_dev(gdev->udev);
    kfree(gdev);
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
    return usb_register(&shymaxtic_usb_driver);
}
// function for rmmod module.
static void __exit shymaxtic_usb_driver_exit(void) {
    usb_deregister(&shymaxtic_usb_driver);
}

module_init(shymaxtic_usb_driver_init);
module_exit(shymaxtic_usb_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shymaxtic");
MODULE_DESCRIPTION("Shymaxtic USB driver");