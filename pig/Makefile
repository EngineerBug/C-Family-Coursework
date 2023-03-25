# define any contant values
CC = gcc

all : main test

test : pig.c test_pig.c
	$(CC) test_pig.c -o test

main : pig.c piglatin.c
	$(CC) piglatin.c -o main

# clean:
# 	rm *.o