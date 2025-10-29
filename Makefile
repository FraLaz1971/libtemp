CC=gcc -g -O2
LD=gcc
CFLAGS=
LDFLAGS=
LIBS=-lm
RM=rm -rf

.PHONY: all clean

all: mfile1 mfile2 mfile3

lfile1.o: lfile1.c
	$(CC) -c $<
mfile1.o: mfile1.c
	$(CC) -c $<
mfile2.o: mfile2.c
	$(CC) -c $<
mfile3.o: mfile3.c
	$(CC) -c $<
mfile1: mfile1.o lfile1.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile2: mfile2.o lfile1.o lfile2.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile3: mfile3.o lfile1.o lfile2.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
clean:
	$(RM) *.o mfile1 mfile2 mfile3
