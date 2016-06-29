CFLAGS	= -Wall -O2 -static -march=armv7-a
CC	= arm-linux-gnueabi-g++-5
LIBS	= -lpthread -lm -std=c++11
APPS	= ep-cpp-cross

all: $(APPS)

ep-cpp-cross: ep-cpp.cpp
	$(CC) $(CFLAGS) ep-cpp.cpp -o ep-cpp-cross $(LIBS)

clean:
	rm -f *.o $(APPS) 
