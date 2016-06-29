CC		= gcc
LIBS	= -lpthread -fcilkplus -lcilkrts -lm
APPS 	= ep-pthreads-cilk

all: $(APPS)

ep-pthreads-cilk: ep-pthreads-cilk.c
	$(CC) ep-pthreads-cilk.c -o ep-pthreads-cilk $(LIBS)

clean:
	rm -f *.o $(APPS) 
