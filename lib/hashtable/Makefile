# Makefile for 'hashtable' module
#
# Daniel Moder, July 2016

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = hashtabletest
OBJS = hashtabletest.o hashtable.o jhash.o ../set/set.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@


hashtabletest.o: hashtable.h
hashtable.o: hashtable.h jhash.h ../set/set.h
jhash.o: jhash.h
../set/set.o: ../set/set.h

clean:
	rm -f *~
	rm -f *.o
	rm -rf $(PROG).dSYM
	rm -f ../set/set.o
	rm -f $(PROG)
