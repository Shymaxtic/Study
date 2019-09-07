#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>


// probe function
// Called on device insertion
static int pen_probe(struct usb_interface* interface, const struct usb_device_id* id) {
	printk(KERN_INFO "[*] Shymaxtic drive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0; // return 0 indicates we will manage this device.
}

// Disconnect
static void pen_disconnect(struct usb_interface* interface) {
	printk(KERN_INFO "[*] Shymaxtic drive removed\n");
}

// usb device id
static struct usb_device_id pen_table[] = {
	{USB_DEVICE(0x090c, 0x1000)},
		{} // terminating entry.
};
MODULE_DEVICE_TABLE(usb, pen_table);


// usb driver.
static struct usb_driver pen_driver = {
	.name = "Shymaxtic USB driver",
	.id_table = pen_table, // usb device id.
	.probe = pen_probe,
	.disconnect = pen_disconnect,
};

static int __init pen_init(void) {
	int ret = -1;
	printk(KERN_INFO "[*] Shymaxtic drive constructor");
	printk(KERN_INFO "\tRegistering Driver with Kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\tRegistration is complete");
	return ret;
}

static void __exit pen_exit(void) {
	printk(KERN_INFO "[*] Shymaxtic drive destructor");
	usb_deregister(&pen_driver);
	printk(KERN_INFO "\tUnregistration is complete");
}

module_init(pen_init);
module_exit(pen_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shymaxtic");
MODULE_DESCRIPTION("Shymaxtic USB Driver");

