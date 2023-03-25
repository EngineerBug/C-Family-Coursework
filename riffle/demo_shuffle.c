#include <assert.h>
#include "riffle.h"
#include "riffle.c"

/*main function*/
int main(){
    /*create arrays to run tests on*/
    int L[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    char * greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", 
                        "eta", "theta", "iota", "kappa", "lambda", "mu",};

    /*RIFFLING*/
    /*check with integers 1..20*/
    riffle(L, sizeof(L)/sizeof(L[0]), sizeof(L[0]), 15);
    printf("Shuffled integers: ");
    int i;
    for(i = 0; i < 20; i++){
        printf("%d ", L[i]);
    }
    printf("\n");

    /*check with strings*/
    riffle(greek, sizeof(greek)/sizeof(greek[0]), sizeof(greek[0]), 15);
    printf("Shuffled strings: ");
    for(i = 0; i < 12; i++){
        printf("%s ", greek[i]);
    }
    printf("\n");

    /*CHECKING*/
    assert(check_shuffle(L, sizeof(L)/sizeof(L[0]), sizeof(L[0]), cmpInt) == 1);
    assert(check_shuffle(greek, sizeof(greek)/sizeof(greek[0]), sizeof(greek[0]), cmpChar) == 1);

    int ints[5] = {1,2,3,4,5};
    int reverse[5] = {5,4,3,2,1};
    int shuffled[5] = {2,1,4,3,6};
    assert(quality(ints, 5) == 1);
    assert(quality(reverse, 5) == 0);
    assert(quality(shuffled, 5) == 0.5);
    
    return 0;
}