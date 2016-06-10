CFLAGS	= -Wall -O2
CC		= gcc
LIBS	= -lpthread -lm
APPS 	= ep-pthreads

all: $(APPS)

ep-pthreads: ep-pthreads.c
	$(CC) $(CFLAGS) ep-pthreads.c -o ep-pthreads $(LIBS)

clean:
	rm -f *.o $(APPS) 
