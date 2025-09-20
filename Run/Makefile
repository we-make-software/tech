KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
EXTRA_CFLAGS += -I../System
KBUILD_EXTRA_SYMBOLS := ../System/Module.symvers

Project := $(notdir $(shell pwd))
SRC := .c
OBJ := $(SRC:.c=.o)

obj-m := $(Project).o
$(Project)-objs := $(OBJ)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

start: all
	sudo insmod $(Project).ko

stop:
	sudo rmmod $(Project).ko
	make clean
