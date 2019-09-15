# obj-m := nulldriver.o
# obj-m := shymaxtic_usb_driver.o
obj-m := shymaxtic_usb_device.o
shymaxtic_usb_device-y := shymaxtic_usb_driver.o \
				shymaxtic_device.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
	
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~