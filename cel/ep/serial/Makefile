CFLAGS	= -Wall -O2
CC	= arm-linux-gnueabi-gcc
LIBS	= -lm -static
APPS	= ep-serial-cross

all: $(APPS)

ep-serial-cross: ep-serial.c
	$(CC) $(CFLAGS) ep-serial.c -o ep-serial-cross $(LIBS)

clean:
	rm -f *.o $(APPS) 
