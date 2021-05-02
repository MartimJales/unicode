CC = gcc
FLAGS= -std=c99 -Wextra -O2 -D_GNU_SOURCE

all: g1 g2 g3 g4 parse stack allprog
	
g1: g1.c g1.h
	$(CC) $(FLAGS) -o g1.o  -c g1.c

g2: g2.c g2.h
	$(CC) $(FLAGS) -o g2.o  -c g2.c

g3: g3.c g3.h
	$(CC) $(FLAGS) -o g3.o  -c g3.c

g4: g4.c g4.h
	$(CC) $(FLAGS) -o g4.o  -c g4.c

stack: stack.c stack.h
	$(CC) $(FLAGS) -o stack.o  -c stack.c
	
parse: parse.c parse.h
	$(CC) $(FLAGS) -o parse.o  -c parse.c

allprog: main.c g1.o g2.o g3.o g4.o  stack.o parse.o
	$(CC) $(FLAGS) main.c g1.o g2.o g3.o g4.o  stack.o parse.o -o program -lm

memcheck:
	valgrind --leak-check=yes ./program

clean:
	rm -rf *.o program