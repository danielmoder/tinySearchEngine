# Makefile TEMPLATE for 'cs50ds' library
#   Builds and compiles all the data structures into a library.
#
# David Kotz, April 2016
# updated by Xia Zhou, July 2016
H = hashtable
S = set
C = counters
B = bag
M = memory


OBJS = $M/memory.o $B/bag.o $C/counters.o $S/set.o $H/hashtable.o
LIB = cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$H -I$S -I$C -I$B -I$M
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files


memory.o: memory.h
	cd memory; $(MAKE)
bag.o: bag.h
	cd bag; $(MAKE) bag.o
set.o: set.h
	cd set; $(MAKE) set.o
counters.o: counters.h
	cd counters; $(MAKE) counters.o
hashtable.o: hashtable.h jhash.h set.h
	cd hashtable; $(MAKE) hashtable.o


# add cleanup commands for other subdirectories
.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)
	cd memory; $(MAKE) $@
	cd bag; $(MAKE) $@
	cd counters; $(MAKE) $@
	cd set; $(MAKE) $@
	cd hashtable; $(MAKE) $@
