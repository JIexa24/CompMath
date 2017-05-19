CC = gcc
CFLAGS = -g3 -std=c99 -lm -g

all: ./obj/main.o ./obj/main.o
	$(CC) ./obj/main.o -o ./bin/main -lm

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)


clean:
	rm ./obj/*.o
