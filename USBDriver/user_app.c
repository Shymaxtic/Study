#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define D_DEV   "/dev/shymaxticdevice"

int main () {
    int i, fd;
    char ch, write_buf[100], read_buf[100];

    fd = open(D_DEV, O_RDWR);

    if (fd == -1) {
        printf("File %s either does not exist of has been locked by another process\n", D_DEV);
        exit(-1);
    }
    printf("r = read from device\nw = write from device\nenter command: ");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'w':
        printf("enter data: ");
        scanf(" %[^\n]", write_buf);
        write(fd, write_buf, sizeof(write_buf));
        break;
    case 'r':
        read(fd, read_buf, sizeof(read_buf));
        printf("shymaxticdevice: %s\n", read_buf);
        break;
    default:
        printf("Invalid command");
        break;
    }

    close(fd);
    return 0;
}