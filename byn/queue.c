/*Program headers*/
#include "beggar.h"



/*Function prototypes*/
/*CREATION*/
QUEUE * createQueue();
NODE * createNode(int);
void freeQueue(QUEUE*);
/*MODIFICATION*/
void push(QUEUE*, int);
int pop(QUEUE*);
void queueMove(QUEUE*, QUEUE*);
void queueCpy(QUEUE*, QUEUE*);
/*INFORMATION*/
void toString(QUEUE*);
int length(QUEUE*);

/*CREATION*/

/*Create an empty queue*/
QUEUE * createQueue(){
    /*Create a queue with enough memory for a head.*/
    QUEUE * newQueue = malloc(sizeof(QUEUE));
    if(!newQueue){
        return NULL;
    }
    newQueue->head = NULL;
    return newQueue;
}

/*Create a new node*/
NODE * createNode(int element){
    /*Create a node with enough memory to store the int and pointer.*/
    NODE * newNode = malloc(sizeof(NODE));
    /*Has the node been created?*/
    if(!newNode){
        return NULL;
    }
    /*Assign the element to the node and instantiate the pointer.*/
    newNode->element = element;
    newNode->nextElement = NULL;
    return newNode;
}

/**
 * Store the first and second memeber of the queue.
 * While there is still a node in the queue.
 *      Free the current node.
 *      Store the next node.
 * Free the last node.
 * Free the queue.
 * 
 * @param queue the queue to free
*/
void freeQueue(QUEUE * queue){
    NODE * currentNode;
    NODE * nextNode = queue->head;
    /*free every node*/
    while(nextNode){
        currentNode = nextNode;
        nextNode = nextNode->nextElement;

        free(currentNode);
    }
    free(queue);
}

/*MODIFICATION*/

/**
 * Adds an element into the end of a queue.
 * 
 * If the queue is empty, update the head of the queue.
 * Iterate through each element until one does not point to an element.
 * Create a new node and assign the previous last element to point to it.
 * 
 * @param queue the queue to add the element to
 * @param element the element to add to the queue
 * 
*/
void push(QUEUE * queue, int element){
    NODE * newNode = createNode(element);
    /*Is the list empty?*/
    if(!queue->head){
        /*Instantiate the first element*/
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        /*Find the next element and add a pointer to a new element.*/
        NODE * currentNode = queue->tail;
        
        /*When the last node is found, make it point to the new node.*/
        currentNode->nextElement =  newNode;
        queue->tail = newNode;
    }
}

/**
 * Removes the first element from the queue and returns it.
 * 
 * Check if the queue is empty.
 * Check if the queue only has one element.
 * 
 * Free the old node and return the value.
 * 
 * @param queue the queue to remove the element from
 * @return the value of the element removed from the queue
*/
int pop(QUEUE * queue){
    NODE * oldNode = queue->head;

    if(!oldNode) return 0;
    if(!oldNode->nextElement) queue->tail = NULL;

    /*free the old node and return the value*/
    int element = queue->head->element;
    queue->head = queue->head->nextElement;
    free(oldNode);
    return element;

}

/**
 * Appends the contents of one queue to another.
 * The src queue will become an empty queue.
 * 
 * if neither of the queues are empty:
 *      move the head pointer of src to the next element of bin
 *      move the tail pointer of src to the tail of bin
 * else if bin is empty:
 *      move the head pointer of src to the head of bin
 *      move the tail pointer of src to the tail of bin
 * (phantom else if src is empty:)
 *      do nothing
 * 
 * remove all pointers from src
 * 
 * @param src the source queue
 * @param bin the target queue
 * 
*/
void queueMove(QUEUE * bin, QUEUE * src){
    /*which of the queues (if any) are empty?*/
    if(bin->head && src->head){             /*if neither of them are empty*/
        bin->tail->nextElement = src->head;
        bin->tail = src->tail;
    } else if(!bin->head && src->head) {    /*if bin is empty*/
        bin->head = src->head;
        bin->tail = src->tail;
    }

    /*remove all pointers from src*/
    src->head = NULL;
    src->tail = NULL;
}

/**
 * Appends the contents of one queue to another.
 * Will note empty the src queue.
 * 
 * @param src the source queue
 * @param bin the target queue
 * 
*/
void queueCpy(QUEUE * bin, QUEUE * src){
    if(src->head){
        NODE * currentNode = src->head;
        push(bin, currentNode->element);

        while(currentNode->element){
            currentNode = currentNode->nextElement;
            push(bin, currentNode->element);
        }
    }
}

/*INFORMATION*/

/**
 * Look through each node until one doesn't point to another node.
 * 
 * Check if the queue exists (is not null).
 * Check if the queue is empty.
 * 
 * Iterate through each node until there is no next element.
 * 
 * @param queue the queue to check the length of
 * @return the length of the queue
*/
int length(QUEUE * queue){
    if(!queue) return 0;
    if(!queue->head) return 0;

    int length = 0;
    NODE * currentNode = queue->head;
    while(currentNode){
        length++;
        currentNode = currentNode->nextElement;
    }
    return length;
}

/**
 * Print the contents of the queue.
 * Starts at the oldest element and prints each element until there is no next element.
 * 
 * @param queue the queue to print
*/
void toString(QUEUE * queue){
    /*Is the queue empty?*/
    if(!queue->head){
        printf("Empty\n");
    } else {
        /*Iterate through every node until there is no next element*/
        NODE * currentNode = queue->head;
        printf("HEAD ");
        while(currentNode){
            printf("%d ", currentNode->element);
            currentNode = currentNode->nextElement;
        }
        printf("TAIL\n");
    }
}