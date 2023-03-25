/*header files*/
#include <time.h>
#include "riffle.h"

/*function prototypes*/
/*RIFFLING*/
void riffle(void*, int, int, int);
void riffle_once(void*, int, int, void*);

/*CHECKING*/
int check_shuffle(void*, int, int, int (*)(void *, void *));
int cmpChar(void*, void*);
int cmpInt(void*, void*);

/*QUALITY*/
float average_quality(int, int, int);
float quality(int*, int);

/*function definitions*/
/**
 * Riffle shuffles an array of elements
 * 
 * Create an array to add the riffled elements to, then riffle_once() the array N times.
 * 
 * @param L a pointer to the array
 * @param len the length of the array
 * @param size the size of each element in the array
 * @param N the number of times to riffle shuffle the array
 * @return a pointer to the riffle shuffled array
*/
void riffle(void * L, int len, int size, int N){

    void * work = malloc(len*size);

    int i;
    for(i=0; i<N; i++){
        riffle_once(L, len, size, work);
    }

    free(work);
}

/**
 * Riffle shuffles an array of elements once
 * 
 * Find the midpoint of the array
 * while the array is not fully riffled
 *      randomly choose a side of the array to add from
 *      if either side is empty, add from the other side
 *      add the element
 * 
 * @param L a pointer to the array
 * @param len the length of the array
 * @param size the size of each element in the array
 * @param work a pointer to the array to add the riffled elements to
*/
void riffle_once(void * L, int len, int size, void *work){
    /*create a void pointer to the midpoint of the array*/
    void * mid = L + (len / 2)*size;

    /*create counters for each half of the array*/
    int leftIndex = 0;
    int rightIndex = 0;

    /*generate a sudo-random seed for the random choosing*/
    srand(time(NULL));

    while(leftIndex + rightIndex < len){
        /*choose which side of the array will be added, left = 0, right = 1*/
        int side = rand() % 2;

        /*if either side is empty, add from the other side*/
        if (leftIndex == len / 2){
            side = 1;
        }else if(rightIndex == len / 2){
            side = 0;
        }

        /*add the element*/
        if(side == 0){
            memmove(work + (leftIndex + rightIndex)*size, L + leftIndex*size, size);
            leftIndex++;
        }else{
            memmove(work + (leftIndex + rightIndex)*size, mid + (rightIndex)*size, size);
            rightIndex++;
        }
    }
    memmove(L, work, len*size);
}

/**
 * Checks that a riffle does not lose or gain any elements.
 * 
 * Create a riffled array
 * Casts the comparison function to a qsort compatable function
 * Sort both arrays
 * Compare the elements of the arrays
 * 
 * @param L a pointer to the array
 * @param len the length of the array
 * @param size the size of each element in the array
 * @param cmp a pointer to the comparison function
 * @return 1 if the riffle is valid, 0 if it is not
*/
int check_shuffle(void * L, int len, int size, int (*cmp)(void *, void *)){
    /*create a riffled array to compare the original to*/
    void * work = L;
    riffle(L, len, size, 50);

    /*use a nested function to recast the arguments of cmp*/
    int newCmp(const void *a, const void *b){return cmp((void *)a, (void *)b);}

    /*sort the array*/
    qsort(L, len, size, newCmp);

    /*check the arrays have the same elements*/
    int i;
    for(i=0; i<len; i++){
        if(*(int*)(L+i*size) != *(int*)(work+i*size)){
            return 0;
        }
    }
    return 1;
}

/**
 * Compare two integers
 * 
 * @param a a pointer to the first integer
 * @param b a pointer to the second integer
 * @return 1 if a > b, -1 if a < b, 0 if a == b
*/
int cmpInt(void * a, void * b) {
    if ( *(int*)a > *(int*)b )
        return 1;
    else if ( *(int*)a < *(int*)b )
        return -1;

    return 0;
}

/**
 * Compare two characters
 * 
 * @param a a pointer to the first character
 * @param b a pointer to the second character
 * @return 1 if a > b, -1 if a < b, 0 if a == b
*/
int cmpChar(void * a, void * b) {
    if ( *(char*)a > *(char*)b )
        return 1;
    else if ( *(char*)a < *(char*)b )
        return -1;

    return 0;
}

/**
 * Calculate how shuffled an array of integers is.
 * 
 * Check every pair of numbers in the array
 * If the first number is less than the second, it is still ordered.
 * 
 * Claculate the fraction of ordered pairs.
 * In an ordered list, this will be 1.
 * In a reversed list, this will be 0.
 * In a well shuffled list, we should expect this to be close to 0.5
 * 
 * @param numbers a pointer to the array
 * @param len the length of the array
 * @return the fraction of ordered pairs
*/
float quality(int * numbers, int len){
    /*check overy pair of numebrs in the array*/
    int ordered = 0;
    int i;
    for(i=0; i<len-1; i++){
        if(numbers[i] < numbers[i+1]){
            ordered++;
        }
    }
    return (float)ordered/(len-1);
}

/**
 * Calculate the average quality of a riffle shuffle.
 * 
 * Create an array of integers
 * For each trial:
 *    populate the array with sorted elements [0..N-1]
 *    riffle the array 'shuffles' times
 * 
 * @param N the number of elements in the array [0..N-1]
 * @param shuffles the number of times to riffle shuffle the array
 * @param trials the number of times to repeat the experiment (e.g. 30)
 * @return the average quality of the riffle shuffle
*/
float average_quality(int N, int shuffles, int trials){
    /*create the array*/
    int array[N];
    int i;
    for(i=0; i<N; i++){
        array[i] = i;
    }

    /*perform the trials*/
    riffle(array, N, sizeof(array[0]), shuffles);
    float average = quality(array, N);
    for(i=1; i<trials; i++){
        riffle(array, N, sizeof(array[0]), shuffles);
        average += quality(array, N);
    }
    /*return the arerage quality*/
    return average/trials;
}