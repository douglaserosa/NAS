CFLAGS	= -Wall -O2 -fPIE -fPIC
CC		= clang++
LIBS	= -std=c++11 -lm -pie -static-libstdc++ --sysroot=/toolchains/arm/api21/clang/sysroot
APPS	= ep-cpp

all: $(APPS)

ep-cpp: ep-cpp.cpp
	$(CC) $(CFLAGS) ep-cpp.cpp -o ep-cpp $(LIBS)

clean:
	rm -f *.o $(APPS) 
