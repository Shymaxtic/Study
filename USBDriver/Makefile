obj-m := shymaxtic_module.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
	
clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *~