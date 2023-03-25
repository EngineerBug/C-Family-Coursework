#include <assert.h>
#include "riffle.h"
#include "riffle.c"

/*main function*/
int main(){
    /*create arrays to run tests on*/
    int L[10] = {0,1,2,3,4,5,6,7,8,9};
    char * greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", 
                        "eta", "theta", "iota", "kappa", "lambda", "mu",};

    /*RIFFLING*/
    /*check with integers 1..20*/
    riffle(L, sizeof(L)/sizeof(L[0]), sizeof(L[0]), 15);
    printf("Shuffled integers: ");
    int i;
    for(i = 0; i < 10; i++){
        printf("%d ", L[i]);
    }
    printf("\n");
    printf("Quality: %f\n", quality(L, 10));

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
    
    return 0;
}