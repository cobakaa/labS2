
CC = gcc
CCFLAGS = -Wall -pedantic -std=c99
LD = gcc

OBJ = matrix.o main.o

.SUFFIXES: .c .o

main: $(OBJ)
	$(LD) -o main $(OBJ)
	make clean

main.o: main.c matrix.h

.c.o : 
	$(CC) $(CCFLAGS) -c $< -o $@

matrix.c: matrix.h

clean: 
	rm -f *.o