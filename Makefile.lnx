CC=gcc
LD=gcc
CFLAGS=
LDFLAGS=
LIBS=
RM=rm -rf

.PHONY: all clean

all: mfile1

lfile1.o: lfile1.c
	gcc -c $<
mfile1.o: mfile1.c
	gcc -c $<
mfile1: mfile1.o lfile1.o
	$(LD) $^ -o $@
clean:
	$(RM) *.o mfile1
