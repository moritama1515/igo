#Makefile for tamago5.c

tamago: tamago.o display.o
	gcc -o tamago tamago.c display.c

tamago.o: tamago.c
	gcc -c tamago.c
display.o: display.c
	gcc -c display.c

tamago.c: display.h
display.c: display.h