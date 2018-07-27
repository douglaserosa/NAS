CFLAGS	= -Wall -O2
CC		= clang
LIBS	= -lm --sysroot=/toolchains/android/arm/sysroot -pie
APPS 	= ep-pthreads

all: $(APPS)

ep-pthreads: ep-pthreads.c
	$(CC) $(CFLAGS) ep-pthreads.c -o ep-pthreads $(LIBS)

clean:
	rm -f *.o $(APPS) 
