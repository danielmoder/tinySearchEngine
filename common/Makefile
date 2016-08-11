OBJS = file.o index.o web.o webpage.o word.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make


$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files

file.o: file.h
index.o: index.h ../lib/hashtable/hashtable.h ../lib/hashtable/jhash.h ../lib/set/set.h
web.o: web.h
webpage.o: webpage.h ../lib/memory/memory.h
word.o: word.h

# add cleanup commands for other subdirectories
.PHONY: clean

clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)

