make:
	cd common; $(MAKE)
	cd lib; $(MAKE)
	cd crawler; $(MAKE)

clean:
	cd common; $(MAKE) $@
	cd lib; $(MAKE) $@
	cd crawler; $(MAKE) $@


