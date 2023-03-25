#include "beggar.h"
#include "beggar.c"

/*Function Prototypes*/
STAT statistics(int, int);
STAT initStat(int);

/*Main Function*/
/**
 * Plays a number of games of beggar your neighbour and prints the statistics
 * 
 * If the correct arguments are given:
 *      turn the arguments into ints
 *      for each number of players from 2 to Nplayers:
 *          play the number of games given
 *          print the statistics
 * Else:
 *      print an error message
 * 
 * @param argc the number of arguments
 * @param argv the arguments, Nplayers and games
 * @return 0
*/
int main(int argc, char ** argv){
    if(argc == 3 && atoi(argv[1]) > 1 && atoi(argv[2]) > 99){
        /*turn arguments into integers*/
        int Nplayers = atoi(argv[1]);
        int games = atoi(argv[2]);

        /*play games*/
        int i;
        for(i=2; i<=Nplayers; i++){
            STAT stats = statistics(i, games);
            printf("%d: s %d, a %f, l %d\n", i, stats.shortest, stats.average, stats.longest);
        }
    } else {
        printf("Please enter [Nplayers > 1] and [games > 99] when executing.\n");
    }
}

/**
 * Creates a deck of cards
 * Initialises a stat struct
 * For every game:
 *      play a game of beggar your neighbour
 *      update the stats
 * Calculate the average
 * 
 * @param Nplayers the number of players
 * @param games the number of games to play
 * @return the statistics of the games
*/
STAT statistics(int Nplayers, int games){
    /*create the deck of cards*/
    int * deck = malloc(sizeof(int)*52);
    int i;
    for(i=0; i<52; i++) deck[i] = i;

    /*initialise the stats*/
    STAT stats = initStat(beggar(Nplayers, deck, 0));

    /*play the games (1 has already been played)*/
    for(i=2; i<games; i++){
        int newvalue = beggar(Nplayers, deck, 0);

        stats.average += newvalue;

        if(newvalue < stats.shortest) stats.shortest = newvalue;
        if(newvalue > stats.longest) stats.longest = newvalue;
    }

    /*calculate the average*/
    stats.average /= games;

    free(deck);

    return stats;
}
/**
 * Initialises a stat struct
 * 
 * If only one experiment has been done, the shortest, average and longest will be equal
 * 
 * It requires an inital value to be passed to avoid NULL value errors
 * (since NULL cannot be compared or checked for equality to an int)
 * 
 * @param initialValue the value to set all the stats to 
 * @return the initialised stat struct
*/
STAT initStat(int initialValue){
    STAT stats = {initialValue, initialValue, initialValue};
    return stats;
}