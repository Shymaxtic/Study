#ifndef SHYMAXTIC_DEVICE_FILE_IOCTL_H
#define SHYMAXTIC_DEVICE_FILE_IOCTL_H
#include <stdint.h>


#define IOCTL_SHYMAXTIC_PING            _IOW('s', 102, uint32_t)
#define IOCTL_SHYMAXTIC_GET_BAUDRATE    _IOR('s', 103, uint64_t)

#endif