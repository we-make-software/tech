
all:
	$(MAKE) -C System start
	$(MAKE) -C NetworkAdapter start
	$(MAKE) -C Run start

stop:
	$(MAKE) -C Run stop
	$(MAKE) -C NetworkAdapter stop
	$(MAKE) -C System stop

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
