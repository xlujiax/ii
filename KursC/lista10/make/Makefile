all: zad3

bitvector:
	gcc -c bitvector.c

queue: list
	gcc -c queue.c

list:
	gcc -c list.c

graph: bitvector queue list
	gcc -c graph.c

zad3: bitvector queue list graph
	gcc -c zad3.c -o zad3.exe