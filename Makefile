CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: buildidx key2val val2key  actors bacon1

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o -g

hashfn.o: hashfn.c 
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o -g

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o -g

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o -g

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o -g

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o -g

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o -g

buildidx: buildidx.o hashfn.o util.o
	$(CC) $(CFLAGS) buildidx.o hashfn.o util.o -o buildidx -g

key2val: key2val.o hashfn.o util.o
	$(CC) $(CFLAGS) key2val.o hashfn.o util.o -o key2val -g

val2key: val2key.o hashfn.o util.o
	$(CC) $(CFLAGS) val2key.o hashfn.o util.o -o val2key  -g

actors: actors.o hashfn.o util.o
	$(CC) $(CFLAGS) actors.o hashfn.o util.o -o actors -g

bacon1: bacon1.o hashfn.o util.o
	$(CC) $(CFLAGS) bacon1.o hashfn.o util.o -o bacon1 -g

clean:
	rm -i *.o buildidx key2val val2key actors bacon1 *.khs *.vhs