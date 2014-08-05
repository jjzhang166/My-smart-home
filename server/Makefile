# Top level makefile, the real shit is at src/Makefile

default: all

.DEFAULT:
	cd src && $(MAKE) $@

install:
	echo  $(CURDIR)
	cd src && $(MAKE) PREFIX=$(CURDIR) $@

.PHONY: install
