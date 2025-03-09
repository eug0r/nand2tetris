CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: hack_assembler

hack_assembler: main.o code.o symboltable.o parser.o
	$(CC) main.o code.o symboltable.o parser.o -o hack_assembler

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o hack_assembler
