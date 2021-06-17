ipt-y = ipt-module.o ipt-device.o ipt-processor.o
obj-m = ipt.o

all:
	$(MAKE) -C "/lib/modules/$(shell uname -r)/build" M="$(shell pwd)" modules

clean:
	$(MAKE) -C "/lib/modules/$(shell uname -r)/build" M="$(shell pwd)" clean
