CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -I./include -march=native -O3 -D_POSIX_C_SOURCE=199309L
LIBS=

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)


clean:
	rm -f main main.o
