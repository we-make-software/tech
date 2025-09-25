MODULES_FROM_DIRECTORY := $(shell grep '^#include "' System/Directory.h | sed -e 's/#include "..\\//' -e 's/\.h"//')

MODULES := System $(MODULES_FROM_DIRECTORY) Run

REVERSE = $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1))) $(firstword $(1)))

REVERSE_MODULES := $(call REVERSE,$(MODULES))

all:
	@for m in $(MODULES); do \
		$(MAKE) -C $$m start || true; \
	done

stop:
	@for m in $(REVERSE_MODULES); do \
		$(MAKE) -C $$m stop || $(MAKE) -C $$m clean || true; \
	done

log:
	sudo dmesg -w

clean:
	sudo dmesg -C

test:
	make all
	make log

github:
	git add .
	git commit -m "Auto-commit $(shell date '+%Y-%m-%d %H:%M:%S')"
	git push origin main

