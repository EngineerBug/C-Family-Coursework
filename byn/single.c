#include "beggar.h"
#include "beggar.c"

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