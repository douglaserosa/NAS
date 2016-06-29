CFLAGS	= -Wall -O2
CC		= mpicc
LIBS	= -lm
APPS	= ep-mpi

all: $(APPS)

ep-mpi: ep-mpi.c
	$(CC) $(CFLAGS) ep-mpi.c -o ep-mpi $(LIBS)

clean:
	rm -f *.o $(APPS) 
