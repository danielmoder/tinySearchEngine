L = ../lib
C = ../common

PROG = indexer # indextest
# OBJS = indexer.o ../lib/hashtable/hashtable.o ../lib/hashtable/jhash.o ../lib/set/set.h ../lib/memory/memory.o ../common/index.o ../common/webpage.o ../common/word.o
LIBS = 
LLIBS = ../lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

#all: indexer indextest

# build the indexer
$(PROG): indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# indexer source dependencies; add others as needed
hashtable/hashtable.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/set/set.h
$L/hashtable/jhash.o:
$L/memory/memory.o:
$C/index.o:
$C/webpage.o:
$C/word.o:



indexer.o: ../common/index.h ../lib/hashtable/jhash.h



# build the library
../lib/cs50ds.a:
	cd ../lib; $(MAKE)
../common/common.a:
	cd ../common; $(MAKE)

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	cd ../lib; $(MAKE) clean
	cd ../common; $(MAKE) clean
