
CC = gcc
CCFLAGS = -Wall -pedantic -std=c99
LD = gcc

OBJ = list.o main.o

.SUFFIXES: .c .o

main: $(OBJ)
	$(LD) -o main $(OBJ)
	make clean

main.o: main.c list.c

.c.o : 
	$(CC) $(CCFLAGS) -c $< -o $@

list.c: list.h

clean: 
	rm -f *.o