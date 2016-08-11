L = ../lib
C = ../common

PROG = querier
OBJS = querier.o
LLIBS = $C/common.a $L/cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

querier.o:


$L/cs50ds.a:
	cd $L; $(MAKE)
$C/common.a:
	cd $C; $(MAKE)

.PHONY: clean

clean:
	rm -f *.o
	rm -f $(PROG)
	cd $L; $(MAKE) $@
	cd $C; $(MAKE) $@
