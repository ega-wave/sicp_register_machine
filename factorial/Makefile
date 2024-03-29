
all : factorial

CFLAGS=-g

FACTORIAL_OBJS=factorial.o

factorial : $(FACTORIAL_OBJS)
	g++ $(CFLAGS) -o factorial $(FACTORIAL_OBJS)

factorial.o : factorial.cpp
	g++ $(CFLAGS) -c factorial.cpp -o factorial.o

test : factorial
	bash factorial_test.sh

clean :
	rm -f factorial *.o

.PHONY: test clean

