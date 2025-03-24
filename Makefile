# Build Script

TARGET = hgh
CC = gcc

$(TARGET): main.o

main.o:
	$(CC) main.c lexer/lexer.c lexer/token.c -o hgh
