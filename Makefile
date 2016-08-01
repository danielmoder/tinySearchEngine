make:
	cd common; $(MAKE)
	cd lib; $(MAKE)
	cd crawler; $(MAKE)
	cd indexer; $(MAKE)

clean:
	cd common; $(MAKE) $@
	cd lib; $(MAKE) $@
	cd crawler; $(MAKE) $@
	cd indexer; $(MAKE) $@

