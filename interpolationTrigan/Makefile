CC = gcc
CFLAGS = -g3 -std=c99 -lm 

all: ./obj/main.o ./obj/main.o
	$(CC) ./obj/main.o -o ./bin/main $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)


clean:
	rm ./obj/*.o
