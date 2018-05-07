CFLAGS	= -Wall -O2 -std=c++11
CC		= clang++
LIBS	= --sysroot=/toolchains/android/arm/sysroot -pie -static-libstdc++
APPS	= battery

all: $(APPS)

battery: battery.cpp
	$(CC) $(CFLAGS) battery.cpp -o battery $(LIBS)

clean:
	rm -f *.o $(APPS) 
