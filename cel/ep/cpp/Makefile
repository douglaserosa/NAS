CFLAGS	= -Wall -O2
CC		= clang++
LIBS	= -std=c++11 -lm --sysroot=/toolchains/android/arm/sysroot -pie -static-libstdc++
APPS	= ep-cpp

all: $(APPS)

ep-cpp: ep-cpp.cpp
	$(CC) $(CFLAGS) ep-cpp.cpp -o ep-cpp $(LIBS)

clean:
	rm -f *.o $(APPS) 
