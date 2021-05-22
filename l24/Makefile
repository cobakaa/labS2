CC = gcc
CFLAGS = -g -pedantic -Wall -std=c99 -Werror
LMFLAG = -lm
OBJ = token.o vector.o rpn.o stack.o tree.o main.o
PROG = lab24

all: token.o vector.o rpn.o stack.o tree.o main.o
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LMFLAG)
	make clean

token.o: token.c
	$(CC) $(CFLAGS) -c token.c

rpn.o: rpn.c
	$(CC) $(CFLAGS) -c rpn.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ)

cleanall:
	rm -f $(PROG)  $(OBJ)