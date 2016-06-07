INCL	= -L/usr/src/linux-headers-4.4.0-22/include/linux/mpi.h
CFLAGS	= -Wall $(INCL) -std=c99 -O2
LIBS	= -lmpi -lm
CC		= gcc

APPS	= ep-mpi

all:	$(APPS)
ep-mpi:	ep-mpi.c
	$(CC) ep-mpi.c -o ep-mpi $(LIBS) $(INCL)

clean:
	rm -f *.o ep-zpl_dbg ep-zpl_real $(APPS) 
