#include "shymaxtic_device.h"

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
