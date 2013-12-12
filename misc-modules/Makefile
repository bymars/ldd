ifneq ($(KERNELRELEASE),)
	# Here means called from kernel built system
	obj-m := hello.o hellop.o
else
	# Here means called from source code directory
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules-install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) module-install
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order  Module.symvers
