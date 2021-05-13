
CC = gcc
CCFLAGS = -Wall -pedantic -std=c99
LD = gcc

OBJ = list.o vector.o main.o

.SUFFIXES: .c .o

main: $(OBJ)
	$(LD) -o main $(OBJ)
	make clean

main.o: main.c vector.c list.c

.c.o : 
	$(CC) $(CCFLAGS) -c $< -o $@

list.c: list.h vector.h

vector.c: vector.h

clean: 
	rm -f *.o