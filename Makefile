CC = gcc
CFLAGS = -g3 -O0 -fopenmp -std=c99

all: GAUSS MPIZ LB3 INTER INTEG SNU

GAUSS:
	make -C gauss
MPIZ:
	make -C mpiz
LB3:
	make -C lb3

INTER:
	make -C interpolationNewton
	make -C interpolationLagrange
	make -C interpolationEitken
	make -C interpolationSpline
	make -C interpolationTrigan

INTEG:
	make -C integrationTrap
SNU:
	make -C SNUNewtoon

clean:
	rm -f ./gauss/obj/*.o
	rm -f ./mpiz/obj/*.o
	rm -f ./lb3/obj/*.o
	rm -f ./interpolationLagrange/obj/*.o
	rm -f ./interpolationEitken/obj/*.o
	rm -f ./interpolationNewton/obj/*.o
	rm -f ./SNUNewtoon/obj/*.o

restruct:
	make clean
	make all
