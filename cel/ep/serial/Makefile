CFLAGS	= -Wall -O2 -fPIE -fPIC
CC		= clang
LIBS	= -lm -pie --sysroot=/toolchains/arm/api21/clang/sysroot
APPS 	= ep-serial

all: $(APPS)

ep-serial: ep-serial.c
	$(CC) $(CFLAGS) ep-serial.c -o ep-serial $(LIBS)

clean:
	rm -f *.o $(APPS) 
