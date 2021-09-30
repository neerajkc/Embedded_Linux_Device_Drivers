obj-m := pcd.o

ARCH=arm
CROSS_COMPILE=arm-linux-gnueabihf-
# KERN_DIR assumes that the embedded kernel was build and installed in the host for linking and cross-compiling.
# Change the version to the installed one.
KERN_DIR=/lib/modules/4.14.108/build/
HOST_KERN_DIR=/lib/modules/$(shell uname -r)/build/

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) modules

clean:
	make -C $(HOST_KERN_DIR) M=$(PWD) clean
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) clean
	
help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) help
	
host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules
	
