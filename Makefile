CC = gcc
CFLAGS = -g3 -O0 -fopenmp -std=c99 

all: GAUSS MPIZ LB3

GAUSS:
	make -C gauss
MPIZ:
	make -C mpiz
LB3:
	make -C lb3

clean:
	rm ./gauss/obj/*.o
	rm ./mpiz/obj/*.o
