/****
    *@author: Samuel Bunyan, Faith Kilonzi(testing)
    *File: concurrentCounter.c

    ***Project 4***Operating Systems****

    *Brief: This program implements a concurrent Counter 
    *such that safe multithreading is enabled.
***/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 

//define the counter and the locks
typedef struct __counter_t {
	int value;
	pthread_mutex_t lock;
} counter_t;

//initialize the counter with lock
void init(counter_t *c) {
	c->value = 0;
	pthread_mutex_init(&c->lock, NULL);
 }

//increment the counter with the locks done
void increment(counter_t *c) {
 	pthread_mutex_lock(&c->lock);
 	c->value++;
 	pthread_mutex_unlock(&c->lock);
}

//decrement the counter with the locks done
 void decrement(counter_t *c) {
 	pthread_mutex_lock(&c->lock);
 	c->value--;
 	pthread_mutex_unlock(&c->lock);
 }

//get the value of the counter while protecting the critical section
 int get(counter_t *c) {
 	pthread_mutex_lock(&c->lock);
 	int rc = c->value;
 	pthread_mutex_unlock(&c->lock);
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
     printf("#Counter with locks :\n");
     init(&myCounter);
     printf("START (counter = %d)\n", get(&myCounter));
     pthread_create(&t1, NULL, executable, &myCounter);
     pthread_create(&t2, NULL, executable, &myCounter);
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
     printf("Counter for 2 threads Done(counter = %d)\n", get(&myCounter));
     return 0;

 }