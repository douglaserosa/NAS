CFLAGS	= -Wall -O2
CC		= clang
LIBS	= -lm --sysroot=/toolchains/android/arm/sysroot -pie
APPS 	= ep-serial

all: $(APPS)

ep-serial: ep-serial.c
	$(CC) $(CFLAGS) ep-serial.c -o ep-serial $(LIBS)

clean:
	rm -f *.o $(APPS) 
