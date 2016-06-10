CFLAGS	= -Wall -O2
CC		= gcc
LIBS	= -fopenmp -lm
APPS	= ep-openmp

all: $(APPS)

ep-openmp: ep-openmp.c
	$(CC) $(CFLAGS) ep-openmp.c -o ep-openmp $(LIBS)

clean:
	rm -f *.o $(APPS) 
