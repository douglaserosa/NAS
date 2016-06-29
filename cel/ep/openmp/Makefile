CFLAGS	= -Wall -O2
CC	= arm-linux-gnueabi-gcc
LIBS	= -fopenmp -lm -static
APPS	= ep-openmp-cross

all: $(APPS)

ep-openmp-cross: ep-openmp.c
	$(CC) $(CFLAGS) ep-openmp.c -o ep-openmp-cross $(LIBS)

clean:
	rm -f *.o $(APPS) 
