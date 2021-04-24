
CC = gcc
CCFLAGS = -Wall -pedantic -std=c99
LD = gcc

OBJ = vector.o stack.o merge_sort.o main.o

.SUFFIXES: .c .o

main: $(OBJ)
	$(LD) -o main $(OBJ)

main.o: main.c vector.h stack.h merge_sort.h

.c.o : 
	$(CC) $(CCFLAGS) -c $< -o $@

vector.c: vector.h

stack.c: stack.h

merge_sort.c: merge_sort.h


clean: 
	rm -f *.o