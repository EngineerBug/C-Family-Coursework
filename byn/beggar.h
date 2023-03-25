#ifndef BEGGAR_H
#define BEGGAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#endif
/**
 * Games can go one for:
 *      a minimum number of rounds
 *      an average number of rounds
 *      a maximum number of rounds
*/
#ifndef STAT
#define STAT struct stats
struct stats {
    int shortest;
    float average;
    int longest;
};
#endif

/**
 * Since Beggar Your Neighbour only requires numbers,
 * These queues only use integers.
 * 
 * Each element points to the next element in the queue.
 * 
 * Idearly, a node should not exist apart from a queue.
*/
#ifndef NODE
#define NODE struct node
struct node {
    int element;
    struct node * nextElement;
};
#endif

/**
 * Each queue has a first and last element to 
 * make adding and removing elements easier.
*/
#ifndef QUEUE
#define QUEUE struct queue
struct queue {
  NODE * head;
  NODE * tail;
};
#endif