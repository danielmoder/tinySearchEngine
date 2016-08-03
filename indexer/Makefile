L = ../lib
C = ../common

PROGS = indexer indextest
OBJS = ../lib/hashtable/hashtable.o ../lib/hashtable/jhash.o ../lib/set/set.h ../lib/memory/memory.o ../common/index.o ../common/webpage.o ../common/word.o
<<<<<<< HEAD
LIBS = 
=======
LIBS =
>>>>>>> 1e1b35bf93b975e618fe3808dca593ad05296ef5
LLIBS = $L/cs50ds.a $C/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L/hashtable -I$L/set -I$L/counters  -I$C
CC = gcc
MAKE = make

all: $(PROGS)

<<<<<<< HEAD
# build the indexer
indexer: indexer.o $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
=======
# build the indexer                                                                                                                                                                                                                                                           
indexer: indexer.o $(OBJS) $(LLIBS)
        $(CC) $(CFLAGS) $^ $(LIBS) -o $@
>>>>>>> 1e1b35bf93b975e618fe3808dca593ad05296ef5

# indexer source dependencies; add others as needed                                                                                                                                                                                                                           
indexer.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/memory/memory.h
indexer.o: $C/index.h $C/webpage.h $C/word.h

indextest: indextest.o $(OBJS) $(LLIBS)
<<<<<<< HEAD
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
=======
        $(CC) $(CFLAGS) $^ $(LIBS) -o $@
>>>>>>> 1e1b35bf93b975e618fe3808dca593ad05296ef5

indextest.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/memory/memory.h
indextest.o: $C/index.h $C/webpage.h $C/word.h


hashtable/hashtable.o: $L/hashtable/hashtable.h $L/hashtable/jhash.h $L/set/set.h
hashtable/jhash.o:
memory/memory.o:
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
<<<<<<< HEAD
	rm -f *~
	rm -f *.o
	rm -f $(PROGS)
	cd ../lib; $(MAKE) clean
	cd ../common; $(MAKE) clean
=======
        rm -f *~
        rm -f *.o
        rm -f $(PROGS)
        cd ../lib; $(MAKE) clean
        cd ../common; $(MAKE) clean
>>>>>>> 1e1b35bf93b975e618fe3808dca593ad05296ef5
