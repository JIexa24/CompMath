CC = gcc
CFLAGS = -g3 -std=c99

all: ./obj/mpi.o ./obj/mzeidel.o
	$(CC) ./obj/mpi.o -o ./bin/mpi 
	$(CC) ./obj/mzeidel.o -o ./bin/mzeidel 

./obj/mpi.o: ./src/mpi.c
	$(CC) -c ./src/mpi.c -o ./obj/mpi.o $(CFLAGS)

./obj/mzeidel.o: ./src/mzeidel.c
	$(CC) -c ./src/mzeidel.c -o ./obj/mzeidel.o $(CFLAGS)

clean:
	rm ./obj/*.o
