# Build Script

TARGET = hgh
CC = gcc

$(TARGET): main.o

main.o:
	$(CC) -g -Wall main.c lexer/lexer.c lexer/token.c vm/chunk.c vm/memory.c vm/debug.c vm/value.c vm/vm.c -DDEBUG -o hgh
