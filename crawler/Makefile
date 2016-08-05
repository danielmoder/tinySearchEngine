# Makefile TEMPLATE for 'crawler' module
#
# David Kotz, April 2016
# updated by Xia Zhou, July 2016

PROG = crawler
OBJS = crawler.o ../common/web.o ../lib/hashtable/hashtable.o ../lib/hashtable/jhash.o
LIBS = -lcurl
LLIBS = ../lib/cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

# build the crawler
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# crawler source dependencies; add others as needed
crawler.o: ../common/web.h
web.o: ../common/web.h
hashtable.o: ../lib/hashtable/hashtable.h ../lib/hashtable/jhash.h ../lib/set/set.h
jhash.o: ../lib/hashtable/jhash.h


# build the library
../lib/cs50ds.a:
	cd ../lib; $(MAKE)

.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	rm -f ../common/web.o
	cd ../lib; $(MAKE) clean
