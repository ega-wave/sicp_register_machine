
all : gcd

CFLAGS=-g

GCD_OBJS=gcd.o

gcd : $(GCD_OBJS)
	g++ $(CFLAGS) -o gcd $(GCD_OBJS)

gcd.o : gcd.cpp
	g++ $(CFLAGS) -c gcd.cpp -o gcd.o

test : gcd
	bash test.sh

clean :
	rm -f gcd *.o

.PHONY: test clean

