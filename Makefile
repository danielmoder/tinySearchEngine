	MAKE = make -C

all:
	$(MAKE) crawler
	$(MAKE) indexer
	$(MAKE) lib
	$(MAKE) common

clean: 
	cd crawler; make $@
	cd indexer; make $@
	cd lib; make $@
	cd common; make $@


