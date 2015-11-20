#Makefile for tamago5.c

tamago: tamago5.o display.o
	gcc -o tamago tamago5.c display.c

tamago5.o: tamago5.c
	gcc -c tamago.c
display.o: display.c
	gcc -c display.c

tamago5.c: display.h
display.c: display.h