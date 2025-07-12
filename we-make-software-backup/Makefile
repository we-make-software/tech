
all:
	$(MAKE) -C B start
	$(MAKE) -C C start
	$(MAKE) -C A start

stop:
	$(MAKE) -C A stop
	$(MAKE) -C C stop
	$(MAKE) -C B stop

log:
	sudo dmesg -w