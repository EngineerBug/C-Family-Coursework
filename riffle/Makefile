# define any contant values
CC = gcc

all : main test

test : riffle.c demo_shuffle.c
	$(CC) demo_shuffle.c -o test

main : riffle.c quality.c
	$(CC) quality.c -o main

# clean:
# 	rm *.o