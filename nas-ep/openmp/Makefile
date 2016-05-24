CC = gcc
LIBS = -fopenmp -lm

APPS = ep-openmp

all: $(APPS)

ep-openmp: ep-openmp.c
	$(CC) ep-openmp.c -o ep-openmp $(LIBS)

clean:
	rm -f *.o $(APPS) 
