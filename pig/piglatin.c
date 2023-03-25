#include "pig.h"
#include "pig.c"

/**
 * Repeatedly asks the user for a sentance in English
 * Prints the same sentance in pig latin
 * 
 * Will continue until the user enters a blank line
 * 
*/
int main() {
    char string[50];

    printf("Enter a series of sentaces to translate to pig latin: \n"); 
    while(fgets(string, sizeof(string), stdin)){

        /*if the user enters a blank line, exit the loop*/
        if(strcmp(string, "\n") == 0) break;

        /*remove the newline charecter at the end*/
        string[strcspn(string, "\n")] = '\0';

        /*print out the pig latin charecters*/
        char * token, * rest = string;
        while(token = strsep(&rest, " ")){
            /*translate, print and free the word*/
            char * piggy = pig(token);
            printf("%s ", piggy);
            free(piggy);
        }

        printf("\n");
    }
    return 0;
}