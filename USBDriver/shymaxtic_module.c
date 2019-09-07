#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/fs.h>	// file file_operations structure - which of course allows use to open/close, read/write to device.
#include <linux/cdev.h> // this is a char driver, make cdev available.
#include <linux/semaphore.h> // used to access semaphores, suchronization behaviors.
#include <linux/uaccess.h>	// copy_to_user; copy_form_user


// (1) Create a structure for our fake device.
struct fake_device {
    char data[100];
    struct semaphore sem;
} virtual_device;

// (2) To later register our device, we neeed a cdev object and some other variables.
struct cdev* mcdev;
int major_number;       // will store our maijor number - extracted from dev_t using macro - mknod /dirctor/file c major minor
int ret;                // wile be used to hold return values of functions; this is because kernel stack is very small.
dev_t dev_num;          // will hold major number that kernel gives us.
                        // name--> appears in /proc/devices.
#define DEVICE_NAME     "shymaxticdevice"

// (7) called on device_file open
// inode reference to the file on disk
// and contains information about that file.
// struct file is represents an abstract open file
int device_open(struct inode* inode, struct file* filep) {
    // only allow one process to open this device by using a semaphore as mutual exclusive lock - mutex
    if (down_interruptible(&virtual_device.sem) != 0) {
        printk(KERN_ALERT "shymaxticdevice: could not lock device during open");
        return -1;
    }
    printk(KERN_INFO "shymaxticdevice: Opened device");
    return 0;
}

// (8) called when user wants to get information from the device.
ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCnt, loff_t* curOffset) {
    // take data from kernel space(device) to user space (process)
    // copy_to_user(destinatioin, source, sizeToTransfer)
    printk(KERN_INFO "shymaxticdevice: Reading from device");
    ret = copy_to_user(bufStoreData, virtual_device.data, bufCnt);
    return ret;
}

// (9) called when user wants to send information to the device.
ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCnt, loff_t* curOffset) {
    // send data from user to kernel
    // copy_from_user (dest, src, cnt)
    printk(KERN_INFO "shymaxticdevice: Writting to the device");
    ret = copy_from_user(virtual_device.data, bufSourceData, bufCnt);
    return ret;
}

// (10) called upon user close.
int device_close(struct inode* inode, struct file* filp) {
    // by calling up, which is opposite of down for semaphore, we release the mutex that we obtained at device open.
    up(&virtual_device.sem);
    printk(KERN_INFO "shymaxticdevice: Closed device");
    return 0;
}


// (6) Tell the kernel which functions to call when user operates on our device file.
struct file_operations fops = {
    .owner = THIS_MODULE,     // prevent unloading of this module when operations are in use.
    .open = device_open,       // points to the method to call when opening the device.
    .release = device_close,    // points to the method to call when closing the device.
    .write = device_write,      // points to the method to call when writing to the device.
    .read = device_read        // points to the method to call when reading from the device.
};

static int mydriver_init(void) {
    // (3) Register our device with the system; two steps process.
    // Step (1) use dynamic allocation to assign our device.
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "shymaxticdevice: failed to allocate a major number");
        return ret;
    }
    major_number = MAJOR(dev_num); //extrat the major number and store in our variable (MACRO)
    printk(KERN_INFO "shymaxticdevice: major number is %d", major_number);
    printk(KERN_INFO "Use \"mknod /dev/%s c %d 0\" for device file", DEVICE_NAME, major_number); //dmesg
    // Step (2)
    mcdev = cdev_alloc();  // create our cdev struct, initialized our cdev.
    mcdev->ops = &fops;         // struct file_operations
    mcdev->owner = THIS_MODULE;
    // Now that we created cdev, we have to add it to the kernel
    // int cdev_add(struct cdev* dev, dev_t num, unsigned int count)
    ret = cdev_add(mcdev, dev_num, 1);
    if (ret < 0) {
        printk(KERN_ALERT "Shymatic Device: Unable to add cdev to kernel");
        return ret;
    }
    // (4) Initialize our semaphore
    sema_init(&virtual_device.sem, 1);
    return 0;
}

static void mydriver_exit(void) {
    // (5) unregister everything in reverse order.
    // (a)
    cdev_del(mcdev);
    // (b)
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "shymaxticdevice: Unloaded module");
}

module_init(mydriver_init);
module_exit(mydriver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shymaxtic");
MODULE_DESCRIPTION("Shymaxtic USB Driver");