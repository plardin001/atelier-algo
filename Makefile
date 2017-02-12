FLAGS = -Wall -std=c99

all : set_sentinel
	./a.out


test: test_unitaire.o set_sentinel.o
	gcc $(FLAGS) set_sentinel.o test_unitaire.o
	./a.out

set_sentinel: set_sentinel.o
	gcc $(FLAGS) set_sentinel.o

set_sentinel.o: set_sentinel.h set_sentinel.c set.h
	gcc $(FLAGS) -c set_sentinel.c 

test_unitaire.o: test_unitaire.c
	gcc $(FLAGS) -c test_unitaire.c 
