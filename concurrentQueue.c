/****
	*@author: Faith Kilonzi
	*File: concurrrentQueue.c

	***Project 4***Operating Systems****

	*Brief: This program implements a concurrent queue 
	*such that multi-threading is enabled.
***/


//Importing Libraries
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <assert.h>

//Node initialization with value and the next node pointer
typedef struct __node_t {
	 int value;
	 struct __node_t *next;
 } node_t;

/*Queue struct with the head and tail pointer
   *headLock and tailLock locks for mutual exclusion in the concurrent queue
 */
 typedef struct __queue_t {
	 node_t *head;
	 node_t *tail;
	 pthread_mutex_t headLock;
	pthread_mutex_t tailLock;
	int len;
 } queue_t;


/**
   @void Queue_Init initializes the queue, its size, the head, tail and the two locks to NULL.
**/
 void Queue_Init(queue_t *q) {
	 node_t *tmp = malloc(sizeof(node_t));
	 tmp->next = NULL;
	 q->head = q->tail = tmp;
	 pthread_mutex_init(&q->headLock, NULL);
	 pthread_mutex_init(&q->tailLock, NULL);
	  q->len = 0;
 }

/**
   @void Queue_Enqueue adds a new node value at the tail of the queue
   @value is the integer value to be added to the queue
   @tailLock is used to lock the insertion at the tail of the queue
**/
 void Queue_Enqueue(queue_t *q, int value) {
	 node_t *tmp = malloc(sizeof(node_t));
	 assert(tmp != NULL);
	 tmp->value = value;
	 tmp->next = NULL;

	 pthread_mutex_lock(&q->tailLock);
	 q->tail->next = tmp;
	 q->tail = tmp;
	 q->len++;
	 pthread_mutex_unlock(&q->tailLock);
	  
 }
/**
   @int Queue_Dequeue removes new node value at the head of the queue
   @value is the pointer integer to what is to be removed
   @headLock is used to lock the removal at the head of the queue
   @returns true or false depending on the success of the enqueue or dequeue
**/
 int Queue_Dequeue(queue_t *q, int *value) {
	 pthread_mutex_lock(&q->headLock);
	 node_t *tmp = q->head;
	 node_t *newHead = tmp->next;
	 if (newHead == NULL) {
		 pthread_mutex_unlock(&q->headLock);
		 return -1; // queue was empty
	 }
	 *value = newHead->value;
	 q->head = newHead;
	 q->len--;
	 pthread_mutex_unlock(&q->headLock);
	 free(tmp);
	 return 0;
 }

 /**
   @void printQueue displays all the node values inside the queue
   @both the tailLock and headLock are used to lock the printing loop over the queue
**/
void printQueue(queue_t *q){
	//pthread_mutex_lock(&q->headLock);
	node_t *curr = q->head;
    while (curr) {
		printf("%d",curr->value);
		printf("\n");
		//pthread_mutex_unlock(&q->headLock);
		//pthread_mutex_lock(&q->tailLock);
        curr = curr->next;
    }
   // pthread_mutex_unlock(&q->tailLock);
} 

/**
   @int safeDelete safely deletes a value from the queue as specified by the node
   @value is the node integer to what is to be removed
   @returns true or false depending on the success of the enqueue or dequeue
**/
char* safeDelete(queue_t *q, int value){
	char *ret="value not in queue";
	pthread_mutex_lock(&q->headLock);
	node_t *curr = q->head;
	node_t *prev = NULL;
	while (curr) {
	    if (curr->value == value) {
	        prev->next = curr->next;
	        curr->next = NULL;
	        ret="value in queue and deleted";
	        break;
	    }
	    prev = curr;
	    curr = curr->next;
	}
	pthread_mutex_unlock(&q->headLock);
	return ret;
}

/**
*returns the size

*/
int size(queue_t *q){
	return q->len;
}

/**
*Testing the concurrent queue implementation with multithreads
**/
queue_t myQueue;

void *executable(void *args){

	int i;
    for (i = 0; i < 20000000; i++)
    {
        Queue_Enqueue(&myQueue, i);
        Queue_Dequeue(&myQueue, &i);
        
    }
    printf("%s", " Last Item Enqueued and Dequeued ");
    printf("%d\n", i);
    

    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{

    Queue_Init(&myQueue);
    printf("Testing Enqueue and Dequeue with locks \n");
    pthread_t p1, p2;
    pthread_create(&p1, NULL, executable, &myQueue);
	pthread_create(&p2, NULL, executable, &myQueue);
	//wait for threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
   printf("Testing Concurrent queue with locks Ended successfully \n");

      //testing for delete
   	int val = 10;
   	Queue_Enqueue(&myQueue, val);
   	printf("%s\n", safeDelete(&myQueue,val));
        

}
