CC = gcc
CFLAGS = -g3 -O0 -fopenmp -std=c99 

all: GAUSS MPIZ LB3 INTER

GAUSS:
	make -C gauss
MPIZ:
	make -C mpiz
LB3:
	make -C lb3

INTER:
	make -C interpolationNewton

clean:
	rm ./gauss/obj/*.o
	rm ./mpiz/obj/*.o
