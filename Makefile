CC=gcc -g -O2
LD=gcc
CFLAGS=-I$(CFITSIO_HOME)/include
LDFLAGS=-L$(CFITSIO_HOME)/lib
LIBS=-lm
CFITSIO_LIBS=-lcfitsio -lm
OEXT=.o
EEXT=
RM=rm -rf

.PHONY: all clean

all: mfile1$(EEXT) mfile2$(EEXT) mfile3$(EEXT) mfile4$(EEXT)\
	mfile5$(EEXT) mfile6$(EEXT) mfile7$(EEXT) mfile8$(EEXT) mfile9$(EEXT)
lfile1$(OEXT): lfile1.c
	$(CC) -c $<
lfile2$(OEXT): lfile2.c
	$(CC) -c $<
lfile3$(OEXT): lfile3.c
	$(CC) $(CFLAGS) -c $<
fimage$(OEXT): fimage.c
	$(CC) $(CFLAGS) -c $<
mfile1$(OEXT): mfile1.c
	$(CC) -c $<
mfile2$(OEXT): mfile2.c
	$(CC) -c $<
mfile3$(OEXT): mfile3.c
	$(CC) -c $<
mfile4$(OEXT): mfile4.c
	$(CC) -c $<
mfile5$(OEXT): mfile5.c
	$(CC) $(CFLAGS) -c $<
mfile6$(OEXT): mfile6.c
	$(CC) $(CFLAGS) -c $<
mfile7$(OEXT): mfile7.c
	$(CC) $(CFLAGS) -c $<
mfile8$(OEXT): mfile8.c
	$(CC) $(CFLAGS) -c $<
mfile9$(OEXT): mfile9.c
	$(CC) $(CFLAGS) -c $<
mfile1$(EEXT): mfile1$(OEXT) lfile1$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile2$(EEXT): mfile2$(OEXT) lfile1$(OEXT) lfile2$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile3$(EEXT): mfile3$(OEXT) lfile1$(OEXT) lfile2$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile4$(EEXT): mfile4$(OEXT) lfile1$(OEXT) lfile2$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIBS)
mfile5$(EEXT): mfile5$(OEXT) lfile1$(OEXT) lfile2$(OEXT) lfile3$(OEXT) fimage$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(CFITSIO_LIBS)
mfile6$(EEXT): mfile6$(OEXT)  lfile1$(OEXT) lfile2$(OEXT) lfile3$(OEXT) fimage$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(CFITSIO_LIBS)
mfile7$(EEXT): mfile7$(OEXT)  lfile1$(OEXT) lfile2$(OEXT) lfile3$(OEXT) fimage$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(CFITSIO_LIBS)
mfile8$(EEXT): mfile8$(OEXT)  lfile1$(OEXT) lfile2$(OEXT) lfile3$(OEXT) fimage$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(CFITSIO_LIBS)
mfile9$(EEXT): mfile9$(OEXT) lfile1$(OEXT) lfile2$(OEXT) lfile3$(OEXT) fimage$(OEXT)
	$(LD) $^ -o $@ $(LDFLAGS) $(CFITSIO_LIBS)
clean:
	$(RM) *$(OEXT) mfile1$(EEXT) mfile2$(EEXT) mfile3$(EEXT) mfile4$(EEXT)\
	mfile5$(EEXT) mfile6$(EEXT) mfile7$(EEXT) mfile8$(EEXT) mfile9$(EEXT)
