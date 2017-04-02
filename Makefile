CC = gcc
CFLAGS = -g3 -O0 -fopenmp -std=c99 

all: GAUSS MPIZ

GAUSS:
	make -C gauss
MPIZ:
	make -C mpiz
clean:
	rm ./gauss/obj/*.o
	rm ./mpiz/obj/*.o
