# define any contant values
CC = gcc

all : main test

test : beggar.c single.c
	$(CC) single.c -o test

main : beggar.c byn.c
	$(CC) byn.c -o main
