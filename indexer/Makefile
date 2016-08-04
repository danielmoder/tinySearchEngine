L = ../lib
C = ../common

PROGS = indexer indextest
OBJS = $L/hashtable/hashtable.o $L/hashtable/jhash.o $L/set/set.h $L/memory/memory.o $L/counters/counters.o $C/index.o $C/webpage.o $C/word.o 
LIBS =
LLIBS = $L/cs50ds.a $C/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L/hashtable -I$L/set -I$L/counters  -I$C
CC = gcc
MAKE = make

all: $(PROGS)

# build the indexer
indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# indexer source dependencies; add others as needed
indexer.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/memory/memory.h
indexer.o: $C/index.h $C/webpage.h $C/word.h

indextest: indextest.o $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/memory/memory.h
indextest.o: $C/index.h $C/webpage.h $C/word.h


hashtable/hashtable.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/set/set.h
hashtable/jhash.o:
memory/memory.o:
counters.o:
index.o:
webpage.o:
word.o:

# build the libraries
$L/cs50ds.a:
	cd $L; $(MAKE)
$C/common.a:
	cd $C; $(MAKE)

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROGS)
	cd ../lib; $(MAKE) clean
	cd ../common; $(MAKE) clean
