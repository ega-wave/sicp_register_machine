
all : fib fib2

CFLAGS=-g

FIB_OBJS=fib.o
FIB2_OBJS=fib2.o

fib : $(FIB_OBJS)
	g++ $(CFLAGS) -o fib $(FIB_OBJS)

fib2 : $(FIB2_OBJS)
	g++ $(CFLAGS) -o fib2 $(FIB2_OBJS)

fib.o : fib.cpp
	g++ $(CFLAGS) -c fib.cpp -o fib.o

fib2.o : fib2.cpp
	g++ $(CFLAGS) -c fib2.cpp -o fib2.o

test : fib
	bash test.sh

test2 : fib2
	bash test2.sh

clean :
	rm -f fib fib2 *.o

.PHONY: test clean

