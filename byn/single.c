#include "beggar.h"
#include "beggar.c"

/**
 * If the number of arguments is incorrect:
 *      fail
 * Else:
 *      create a 52 card deck
 *      simulate beggar your neighbour
 * 
 * @param argc the length of argv
 * @param argv a pointer to an array of command-line arguments
*/
int main(int argc, char ** argv){
    if(argc == 2){
        int Nplayers = atoi(argv[1]);

        /*create the deck of cards*/
        int * deck = malloc(sizeof(int)*52);
        int i;
        for(i=0; i<52; i++) deck[i] = i;

        /*play the game*/
        printf("Turns: %d\n", beggar(Nplayers, deck, 0));
    } else {
        printf("Please enter [Nplayers] when executing.\n");
    }
    return 0;
}