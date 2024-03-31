
all : fib

CFLAGS=-g

FIB_OBJS=fib.o

fib : $(FIB_OBJS)
	g++ $(CFLAGS) -o fib $(FIB_OBJS)

fib.o : fib.cpp
	g++ $(CFLAGS) -c fib.cpp -o fib.o

test : fib
	bash test.sh

clean :
	rm -f fib *.o

.PHONY: test clean

