all: build

build: MineSweeper.o TablaStruct.o
	gcc -g -Wall MineSweeper.o TablaStruct.o -o MineSweeper

MineSweeper.o: MineSweeper.c
	gcc -g -Wall -c MineSweeper.c

TablaStruct.o: TablaStruct.c TablaStruct.h
	gcc -g -Wall -c TablaStruct.c

run:
	./MineSweeper
clean:
	rm -f *.o MineSweeper
