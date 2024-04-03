
all : expt_iter

CFLAGS=-g

EXPT_ITER_OBJS=expt_iter.o

expt_iter : $(EXPT_ITER_OBJS)
	g++ $(CFLAGS) -o expt_iter $(EXPT_ITER_OBJS)

expt_iter.o : expt_iter.cpp
	g++ $(CFLAGS) -c expt_iter.cpp -o expt_iter.o

test : expt_iter
	bash test.sh

clean :
	rm -f expt_iter *.o

.PHONY: test clean

