#include <iostream>
#include "../shymaxtic_device_file_ioctl.h"
#include <fcntl.h>
#include <unistd.h>

#define SHYMAXTIC_USB_DEV   "/dev/shymaxticdevice"

int main(int argc, char** argv) {
    // Open device file.
    int ret = 0;
    int fd = 0;
    fd = open(SHYMAXTIC_USB_DEV, O_RDWR);
    if (fd < 0) {
        std::cerr << "ERR: Failed to open file with error: " << (int) fd << std::endl;
        return fd;
    }
    uint32_t dummyVal = 0;
    ret = ioctl(fd, IOCTL_SHYMAXTIC_PING, &dummyVal);
    if (ret != 0) {
        std::cerr << "ERR: Failed to ioctl file with error: " << (int) ret << std::endl;
    }
    close(fd);
    return 0;
}