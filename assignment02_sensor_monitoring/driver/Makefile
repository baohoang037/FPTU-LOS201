obj-m += sms_sensor_driver.o

KDIR ?= /lib/modules/$(shell uname -r)/build
ARM_KDIR ?= $(HOME)/linux-arm-kernel

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

arm:
	$(MAKE) -C $(ARM_KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
