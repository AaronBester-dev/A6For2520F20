CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: buildidx key2val val2key  actors

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn.o: hashfn.c
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o

buildidx: buildidx.o hashfn.o util.o
	$(CC) $(CFLAGS) buildidx.o hashfn.o util.o -o buildidx

key2val: key2val.o hashfn.o util.o
	$(CC) $(CFLAGS) key2val.o hashfn.o util.o -o key2val

val2key: val2key.o hashfn.o util.o
	$(CC) $(CFLAGS) val2key.o hashfn.o util.o -o val2key

actors: actors.o hashfn.o util.o
	$(CC) $(CFLAGS) actors.o hashfn.o util.o -o actors

bacon1: bacon1.o hashfn.o util.o
	$(CC) $(CFLAGS) bacon1.o hashfn.o util.o -o bacon1

clean:
	rm -i *.o buildidx key2val val2key actors bacon1 