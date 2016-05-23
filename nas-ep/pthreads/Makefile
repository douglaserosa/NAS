CFLAGS	= -Wall -O2
CC = gcc
LIBS = -lpthread

APPS	=	\
	ep-pthreads

all:	$(APPS)

ep-pthreads : ep-pthreads.o
	$(CC) -o ep-pthreads ep-pthreads.o $(LIBS) 

clean:
	rm -f *.o $(APPS) 
