# Top level makefile, the real shit is at src/Makefile

default: all

.DEFAULT:
	cd src && $(MAKE) $@
	cd ..
	mkdir -p bin
	cp -f src/redis-server bin

install:
	cd src && $(MAKE) $@

.PHONY: install
