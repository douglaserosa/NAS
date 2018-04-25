CFLAGS	= -Wall -O2
CC		= gcc
LIBS	= -fopenmp -lm
APPS	= ep-openmp ep-openmp-static ep-openmp-dynamic

all: $(APPS)

ep-openmp: ep-openmp.c
	$(CC) $(CFLAGS) ep-openmp.c -o ep-openmp $(LIBS)

ep-openmp-static: ep-openmp-static.c
	$(CC) $(CFLAGS) ep-openmp-static.c -o ep-openmp-static $(LIBS)

ep-openmp-dynamic: ep-openmp-dynamic.c
	$(CC) $(CFLAGS) ep-openmp-dynamic.c -o ep-openmp-dynamic $(LIBS)

clean:
	rm -f *.o $(APPS) 
