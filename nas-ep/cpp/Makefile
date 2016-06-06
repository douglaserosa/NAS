CC = g++
LIBS = -lpthread -lm -std=c++11

APPS = test

all: $(APPS)

test: test.cpp
	$(CC) test.cpp $(LIBS)

clean:
	rm -f *.o $(APPS) 
