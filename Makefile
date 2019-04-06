CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror -g

all: run

clean:
	rm -f *.o *.out

graph.o: src/graph.c include/graph.h include/error.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

network.o: src/network.c include/network.h include/graph.h graph.o
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

rooting-table.out: src/main.c include/graph.h include/network.h graph.o network.o
	$(CC) $(CFLAGS) $< -o $@ -I./include graph.o network.o

debug: rooting-table.out
	valgrind ./$<

run: rooting-table.out
	./$<