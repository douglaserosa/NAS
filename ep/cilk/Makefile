CC		= gcc
LIBS	= -fcilkplus -lcilkrts -lm
APPS	= ep-cilk

all: $(APPS)

ep-cilk: ep-cilk.c
	$(CC) ep-cilk.c -o ep-cilk $(LIBS)

clean:
	rm -f *.o $(APPS) 
