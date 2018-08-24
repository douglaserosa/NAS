CFLAGS	= -Wall -O2 -fPIE -fPIC
CC		= clang
LIBS	= -lm -pie --sysroot=/toolchains/arm/api21/clang/sysroot
APPS 	= ep-pthreads

all: $(APPS)

ep-pthreads: ep-pthreads.c
	$(CC) $(CFLAGS) ep-pthreads.c -o ep-pthreads $(LIBS)

clean:
	rm -f *.o $(APPS) 
