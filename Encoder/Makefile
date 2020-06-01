obj-m += encode.o

KDIR = /usr/src/linux-headers-4.15.0-66-generic

all:
	$(MAKE)  -C $(KDIR)  SUBDIRS=$(PWD) modules

clean:
	rm -rf *.0 *.ko *.mod.* *.symvers *.order

