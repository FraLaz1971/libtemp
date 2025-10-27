CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=
LIBS=-lm
RM=rm -rf

.PHONY: all clean

all: mfile1

lfile1.o: lfile1.c
	$(CC) -c $<
mfile1.o: mfile1.c
	$(CC) -c $<
mfile1: mfile1.o lfile1.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
clean:
	$(RM) *.o mfile1
