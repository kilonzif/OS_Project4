/****
    *@author: Faith Kilonzi
    *File: nQueue.c

    ***Project 4***Operating Systems****

    *Brief: This program implements a NORMAL COUNTER 
    *to test the concurrent COUNTER.
***/


#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 

//define the counter struct
typedef struct __counter_t {
	int value;
	} counter_t;

//initialize the counter
void init(counter_t *c) {
	c->value = 0;
 }

//increase the counter value
void increment(counter_t *c) {

 	c->value++;

}

// decrement the counter value
 void decrement(counter_t *c) {
 	c->value--;
 }

// get the value of the counter
 int get(counter_t *c) {
 	int rc = c->value;
 	return rc;
 }

/**
*Testing the counter implementation with multithreads
**/
 counter_t myCounter;

  void *executable(void *args){
     int i;
     for (i = 0; i < 10000000; i++) {
        increment(&myCounter);
     }
     return NULL;
  }

  int main(int argc, char const *argv[])
  {
      pthread_t t1, t2;
      printf("#Counter without locks :\n");
      init(&myCounter);
      printf("start (counter = %d)\n", get(&myCounter));
      pthread_create(&t1, NULL, executable, &myCounter);
      pthread_create(&t2, NULL, executable, &myCounter);
      pthread_join(t1, NULL);
      pthread_join(t2, NULL);
      printf("Counter for 2 threads Done(counter = %d)\n", get(&myCounter));
      return 0;

  }