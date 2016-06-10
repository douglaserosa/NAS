INCL	= -I/usr/include/mpi
CFLAGS	= -Wall $(INCL) -std=c99 -O2
LIBS	= -lmpi -lm
ZC	= zc

APPS	=	\
	ep-serial \
	ep-mpi \
	ep-zpl

all:	$(APPS)

ep-serial : ep-serial.o
	$(CC) -o ep-serial ep-serial.o $(LIBS) 

ep-mpi:	ep-mpi.o
	$(CC) -o ep-mpi ep-mpi.o $(LIBS)

ep-zpl:	ep-zpl.z
	$(ZC) ep-zpl.z

clean:
	rm -f *.o ep-zpl_dbg ep-zpl_real $(APPS) 
