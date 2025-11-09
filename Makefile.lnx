# =========================================================
#   Makefile.lnx — gcc / gnu make example
# =========================================================
# Build:
#   make -f Makefile.lnx
# Clean:
#   make -f Makefile.lnx clean
# =========================================================

# --- Tools ------------------------------------------------
CC = gcc
LIBTOOL = ar qv
LD = gcc
RM = rm -rf
# --- Flags ------------------------------------------------
#CFITSIO_HOME = /opt/NASA/cfitsio
CFLAGS = -I$(CFITSIO_HOME)/include
LDFLAGS =  
LIBFLAGS = -L$(CFITSIO_HOME)/lib -lcfitsio

# --- Sources ----------------------------------------------
LIBSRCS = lfile1.c lfile2.c lfile3.c fimage.c
LIBOBJS = $(LIBSRCS:.c=.o)

# Build a static library named libfunc.a
LIBTARGET = libfunc.a

# Executables that use libfunc.a
EXESRCS = mfile1.c mfile2.c mfile3.c mfile4.c mfile6.c mfile7.c mfile8.c mfile9.c
EXEOBJS = $(EXESRCS:.c=.o)
EXETARGETS = $(EXESRCS:.c=)

# --- Default target ---------------------------------------
all: $(LIBTARGET) $(EXEOBJS) $(EXETARGETS)

# --- Library build rule -----------------------------------
$(LIBTARGET): $(LIBOBJS)
	$(LIBTOOL) -o $@ $(LIBOBJS)

# --- Executables build rule -------------------------------
# Use a pattern substitution to get corresponding .o names
# for each .exe, e.g. mfile1.o -> mfile1.exe

# --- Compile all .c to .o -------------------------------
.c.o:
	$(CC) $(CFLAGS) -c $<
# --- Executables build rule -------------------------------
.o:
	$(LD) -o $@ $^ $(LIBTARGET) $(LDFLAGS) $(LIBFLAGS)

# --- Clean target -----------------------------------------
clean:
	$(RM) *.o $(EXETARGETS) *.a 
