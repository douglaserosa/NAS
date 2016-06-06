CC = g++
LIBS = -lpthread -lm -std=c++11

APPS = ep-cpp

all: $(APPS)

ep-cpp: ep-cpp.cpp
	$(CC) ep-cpp.cpp -o ep-cpp $(LIBS)

clean:
	rm -f *.o $(APPS) 
