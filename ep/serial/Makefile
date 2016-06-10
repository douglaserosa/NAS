CFLAGS	= -Wall -O2
CC		= gcc
LIBS	= -lm
APPS	= ep-serial

all: $(APPS)

ep-serial: ep-serial.c
	$(CC) $(CFLAGS) ep-serial.c -o ep-serial $(LIBS)

clean:
	rm -f *.o $(APPS) 
