CFLAGS	= -Wall -O2
CC	= arm-linux-gnueabi-gcc
LIBS	= -lpthread -lm -static
APPS 	= ep-pthreads-cross

all: $(APPS)

ep-pthreads-cross: ep-pthreads.c
	$(CC) $(CFLAGS) ep-pthreads.c -o ep-pthreads-cross $(LIBS)

clean:
	rm -f *.o $(APPS) 
