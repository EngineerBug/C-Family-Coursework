/*Includes*/
#include "beggar.h"
#include "queue.c"
#include "../riffle/riffle.c"

/*Function Prototypes*/
int beggar(int, int*, int);
bool finished(QUEUE**, int Nplayers);
bool take_turn(QUEUE*,QUEUE*);

/**
 * Plays a game of beggar your neighbour.
 * Designed to take a deck amde up of four runs of 2-14
 * 
 * Create the players
 * Shuffle and deal the cards
 * While one player doesn't have 52 cards:
 *      Each player still in takes a turn
 *      If the deck is empty, the player plays a single card
 *      If the top card is a numeral, the player plays a single card
 *      If the top card is a court or ace card, the player pays the penalty
 * 
 * @param Nplayers the number of players
 * @param deck an array of integers representing the deck
 * @param talkative 0 if the game should not print anything, 1 otherwise
 * @return the number of turns taken
*/
int beggar(int Nplayers, int * deck, int talkative){
    /*create an array of points to players hands*/
    QUEUE ** players = malloc(sizeof(QUEUE)*Nplayers);
    int i;
    for(i=0; i<Nplayers; i++){
        QUEUE * player = createQueue();
        players[i] = player;
    }

    /*shuffle the inital deck*/
    riffle(deck, 52, sizeof(int), 7);

    /*turn the shuffled deck into a queue*/
    QUEUE * cards = createQueue();

    /*create the deck, this calculation makes arrays of both 2-14(x4) and 1-52 valid decks*/
    for(i=0; i<52; i++) push(cards, (2+deck[i]%13));

    /*deal to the players*/
    for(i=0; i<52; i++) push(players[i%Nplayers], pop(cards));
    
    /*start with the player at index 1, with the player at index 0 assigned to prevplayer*/
    int turns = 0;
    int prevPlayerIndex = 0;
    int currentPlayerIndex = 1;

    /*play the game*/
    while(!finished(players, Nplayers)){
        /*find the next player*/
        currentPlayerIndex = (currentPlayerIndex+1)%Nplayers;
        
        /*is the player still in the game?*/
        if(length(players[currentPlayerIndex]) != 0){
            if(!cards->head || cards->tail->element <= 10){
                /*deck is empty: play a single card*/
                push(cards, pop(players[currentPlayerIndex]));
                prevPlayerIndex = currentPlayerIndex;
            } else {
                /*penalty card: pay the penalty and give the deck to the previous player*/
                if(take_turn(players[currentPlayerIndex], cards)){
                    queueMove(players[prevPlayerIndex], cards);
                } else {
                    /*the penalty is not yet payed*/
                    currentPlayerIndex = prevPlayerIndex;
                }
            }
            turns++;

            /*print the state of the game if requested*/
            if(talkative && turns%Nplayers == 0){
                printf("Turn: %d\n", turns);
                printf("Deck: "); toString(cards);
                int k;
                for(k=0; k<Nplayers; k++){
                    printf("Player %d's hand: ", k+1); toString(players[k]);
                }
            }
        }
    }

    /*free the memory*/
    free(players);
    freeQueue(cards);

    /*return the number of turns*/
    return turns;
}

/**
 * Takes all the hands of the players and checks if any of them have 52 cards.
 * Iterates through the array to find each player's hand and checks the length.
 * 
 * @param players an array of pointers to the players hands
 * @param Nplayers the number of players
 * @return true if any of the players have 52 cards, false otherwise
*/
bool finished(QUEUE ** players, int Nplayers){
    int i;
    for(i=0; i<Nplayers; i++){
        if(length(players[i]) == 52) return true;
    }
    return false;
}

/**
 * Takes a turn for a player who has to pay a penalty
 * .
 * This will only be triggered if a penalty has to be payed, single card turns are handled by
 * the beggar function. 
 * 
 * The reason I make this a void function is because I want to be able to
 * more easily handle the simple turns in beggar, instead of passing QUEUEs back and fourth, I can
 * queueMove() the cards from the pile to the player.
 * 
 * For number of cards:
 *     Take a card from the player
 *     Add it to the pile
 *     If the card is a penalty card, stop paying the penalty
 * 
 * 
 * @param player the player taking the turn
 * @param pile the pile of cards
 * @return true if the hand has been won, false otherwise
*/
bool take_turn(QUEUE * player, QUEUE * pile){
    /*pay the penatly until the indicated number of card, or until another penalty card is played*/
    int i;
    for(i=10; i < pile->tail->element; i++){
        push(pile, pop(player));
        /*has a penalty card just been put down?*/
        if(pile->tail->element > 10) return false;
    }
    return true;
}