CC=gcc
CFLAGS=-Ofast -Wall -Wextra -Werror -g
SFLAGS=-lcsfml-graphics -lcsfml-window -lcsfml-system

run: rooting-table.out
	./$<

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

force.o: src/force.c include/force.h include/graph.h include/network.h
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

rooting-table.out: src/main.c include/network.h minheap.o graph.o network.o force.o
	$(CC) $(CFLAGS) $< -o $@ -I./include minheap.o graph.o network.o force.o $(SFLAGS) -lm

# Pour installer les dépendances
install:
	sudo apt install gcc libcsfml-dev