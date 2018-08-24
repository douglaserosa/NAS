CFLAGS	= -Wall -O2 -fPIE -fPIC
CC		= arm-linux-androideabi-gcc
LIBS	= -fopenmp -lm -pie --sysroot=/toolchains/arm/api21/clang/sysroot
APPS	= ep-openmp ep-openmp-static ep-openmp-dynamic ep-openmp-guided

all: $(APPS)

ep-openmp: ep-openmp.c
	$(CC) $(CFLAGS) ep-openmp.c -o ep-openmp $(LIBS)

ep-openmp-static: ep-openmp-static.c
	$(CC) $(CFLAGS) ep-openmp-static.c -o ep-openmp-static $(LIBS)

ep-openmp-dynamic: ep-openmp-dynamic.c
	$(CC) $(CFLAGS) ep-openmp-dynamic.c -o ep-openmp-dynamic $(LIBS)

ep-openmp-guided: ep-openmp-guided.c
	$(CC) $(CFLAGS) ep-openmp-guided.c -o ep-openmp-guided $(LIBS)

clean:
	rm -f *.o $(APPS) 
