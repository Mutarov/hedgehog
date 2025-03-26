# Build Script

TARGET = hgh
CC = gcc

$(TARGET): main.o

main.o:
	$(CC) -g -Wall main.c lexer/lexer.c lexer/token.c -o hgh
