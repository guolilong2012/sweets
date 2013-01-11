############Makefile for Debian 4.0rc3

target = nl_kernel
obj-m := $(target).o
KERNELDIR = /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KERNELDIR) M=`pwd` modules
install:
	make uninstall
	dmesg -c
	clear
	insmod $(target).ko
	tail -f /var/log/messages
uninstall:
	rmmod $(target).ko
clean:
	rm -rf *.ko *.mod.c *.o
	rm -rf Module.symvers modules.order .*cmd .tmp_versions

