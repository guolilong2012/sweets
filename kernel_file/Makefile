############Makefile for Debian 4.0rc3

target = kernel_file
obj-m := $(target).o
KERNELDIR = /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KERNELDIR) M=`pwd` modules
install:
	insmod $(target).ko
	dmesg -c
uninstall:
	rmmod $(target).ko
clean:
	rm -rf *.ko *.mod.c *.o
	rm -rf Module.symvers modules.order .*cmd .tmp_versions

