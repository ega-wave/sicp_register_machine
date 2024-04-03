
all : expt_recur

CFLAGS=-g

EXPT_RECUR_OBJS=expt_recur.o

expt_recur : $(EXPT_RECUR_OBJS)
	g++ $(CFLAGS) -o expt_recur $(EXPT_RECUR_OBJS)

expt_recur.o : expt_recur.cpp
	g++ $(CFLAGS) -c expt_recur.cpp -o expt_recur.o

test : expt_recur
	bash test.sh

clean :
	rm -f expt_recur *.o

.PHONY: test clean

