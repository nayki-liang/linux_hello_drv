

export ARCH=arm

export CROSS_COMPILE=arm-linux-gnueabihf-sigmastar-9.1.0-

KDIR = /home/nayki_liang/dtof/ssc268/back/kernel
TARGET = linux_hello_drv

$(TARGET)-objs = hello_drv.o

obj-m +=$(TARGET).o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	# $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CROSS_COMPILE)gcc ./hello_app.c -o ./app

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order .*.cmd main