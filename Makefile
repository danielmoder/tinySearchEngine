	MAKE = make -C

all:
	$(MAKE) querier
	$(MAKE) crawler
	$(MAKE) indexer
	$(MAKE) lib
	$(MAKE) common

clean:
	cd querier; make $@
	cd crawler; make $@
	cd indexer; make $@
	cd lib; make $@
	cd common; make $@


