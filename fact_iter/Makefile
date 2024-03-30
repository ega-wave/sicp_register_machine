
all : fact_iter

CFLAGS=-g

FACT_ITER_OBJS=fact_iter.o

fact_iter : $(FACT_ITER_OBJS)
	g++ $(CFLAGS) -o fact_iter $(FACT_ITER_OBJS)

fact_iter.o : fact_iter.cpp
	g++ $(CFLAGS) -c fact_iter.cpp -o fact_iter.o

test : fact_iter
	bash test.sh

clean :
	rm -f fact_iter *.o

.PHONY: test clean

