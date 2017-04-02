CC = gcc
CFLAGS = -g3 -std=c99

all: ./obj/gauss.o
	$(CC) ./obj/gauss.o -o ./bin/gauss 

./obj/gauss.o: ./src/gauss.c
	$(CC) -c ./src/gauss.c -o ./obj/gauss.o $(CFLAGS)

clean:
	rm ./obj/*.o
