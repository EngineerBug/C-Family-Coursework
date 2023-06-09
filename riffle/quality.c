#include "riffle.h"
#include "riffle.c"

/*main function*/
/**
 * Test the quality of riffle shuffles
 * 
 * Test on an array of the numbers [1..50]
 * Use 30 trials of i riffle shuffles
 * Where i is the current iteration of the loop
 * 
 * Save the results to a file.
 */
int main(){
    /*open the file*/
    FILE * file = fopen("quality.txt", "w");
    float best = 1.0f;
    int shuffles = 0;

    /*run the quality tests*/
    int i;
    for(i=1; i<=15; i++){
        float quality = average_quality(50, 30, i);
        /*if the quality improves, update the best guess*/
        if((quality > 0.5 && quality < best) || (quality < 0.5 && quality < best)){
            best = quality;
            shuffles = i;
        }
        /*print the results to the output file if it exists*/
        if(file){
            fprintf(file, "%d: %f\n", i, quality);
        } else {
            printf("%d: %f\n", i, quality);
        }
    }

    /*print the results to the output file if it exists*/
    if(file){
        fprintf(file, "I think that %d is the best number of shuffles.\n", shuffles);
        fprintf(file, "This is because it returned: %f\n\n", best);
        fprintf(file, "According to Bayer and Diaconis (1992) the optimal number of riffles is 7 with a 52 card deck.\n");
        fprintf(file, "https://statweb.stanford.edu/~cgates/PERSI/papers/bayer92.pdf\n");
    } else {
        printf("I think that %d is the best number of shuffles.\n", shuffles);
        printf("This is because it returned: %f\n", best);
        printf("According to Bayer and Diaconis (1992) the optimal number of riffles is 7 with a 52 card deck.\n");
        printf("https://statweb.stanford.edu/~cgates/PERSI/papers/bayer92.pdf\n");
    }

    /*close the file*/
    fclose(file);

    return 0;
}