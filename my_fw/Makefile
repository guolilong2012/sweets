########Makefile for Debian 4.0rc3

MODULE_NAME = my_fw
obj-m := $(MODULE_NAME).o
KERNELDIR = /lib/modules/`uname -r`/build
PWD = `pwd`
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	insmod $(MODULE_NAME).ko
uninstall:
	rmmod $(MODULE_NAME).ko
clean:
	rm -rf *.o *.mod.c *.ko modules.order
	rm -rf Module.symvers .*cmd .tmp_versions
