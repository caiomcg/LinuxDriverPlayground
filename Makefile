TARGET := linux-driver-playground

obj-m += $(TARGET).o
$(TARGET)-objs := main.o fops/ldp_fops.o

KDIR = /usr/src/linux-headers-$(shell uname -r)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	@ echo "Cleaning objects and other stuff"
	@ rm -f *.o *.ko *.mod.* *.symvers *.order .*.cmd
	@ rm -f fops/*.o fops/.*.cmd
