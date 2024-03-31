
all : sqrt

CFLAGS=-g

SQRT_OBJS=sqrt.o

sqrt : $(SQRT_OBJS)
	g++ $(CFLAGS) -o sqrt $(SQRT_OBJS)

sqrt.o : sqrt.cpp
	g++ $(CFLAGS) -c sqrt.cpp -o sqrt.o

test : sqrt
	bash test.sh

clean :
	rm -f sqrt *.o

.PHONY: test clean

