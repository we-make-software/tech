
all:
	$(MAKE) -C System start
	$(MAKE) -C ServiceListener start
	$(MAKE) -C Router start
	$(MAKE) -C TransportLayer start
	$(MAKE) -C NetworkLayer start
	$(MAKE) -C EthernetFrame start
	$(MAKE) -C NetworkAdapter start
	$(MAKE) -C Run start

stop:
	$(MAKE) -C Run stop || $(MAKE) -C Run clean || true
	$(MAKE) -C TransportLayer stop || $(MAKE) -C TransportLayer clean || true
	$(MAKE) -C NetworkLayer stop || $(MAKE) -C NetworkLayer clean || true
	$(MAKE) -C NetworkAdapter stop || $(MAKE) -C NetworkAdapter clean || true
	$(MAKE) -C EthernetFrame stop || $(MAKE) -C EthernetFrame clean || true
	$(MAKE) -C Router stop || $(MAKE) -C Router clean || true
	$(MAKE) -C ServiceListener stop || $(MAKE) -C ServiceListener clean || true
	$(MAKE) -C System stop || $(MAKE) -C System clean || true

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
