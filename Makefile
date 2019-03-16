CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

all: run

clean:
	rm -f *.o *.out

node.o: src/node.c include/node.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

graph.o: src/graph.c include/graph.h include/node.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

rooting-table.out: src/main.c include/node.h node.o include/graph.h graph.o
	$(CC) $(CFLAGS) $< -o $@ -I./include

run: rooting-table.out
	./$<