CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror -g

run: rooting-table.out
	./$<

check-memory: rooting-table.out
	valgrind ./$<

check-time: rooting-table.out
	/usr/bin/time -v ./$<

clean:
	rm -f *.o *.out

minheap.o: src/minheap.c include/error.h include/minheap.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

graph.o: src/graph.c include/error.h include/graph.h include/minheap.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

network.o: src/network.c include/error.h include/graph.h include/network.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

rooting-table.out: src/main.c include/network.h minheap.o graph.o network.o
	$(CC) $(CFLAGS) $< -o $@ -I./include minheap.o graph.o network.o