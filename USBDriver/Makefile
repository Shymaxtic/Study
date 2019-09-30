# CONFIG_MODULE_SIG=n
# obj-m := nulldriver.o
# obj-m := shymaxtic_usb_driver.o
# obj-m := dktm4c123g_usb_driver.o
obj-m := usb_skeleton.o
# obj-m := shymaxtic_usb.o
# shymaxtic_usb-y := shymaxtic_main.o \
# 				shymaxtic_device.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
	
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~