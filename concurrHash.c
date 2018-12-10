
/**
@AUTHOR: YAMOAH BENTIL
FILE: concurrent hashtable.c

***/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "concurrList.h"
#define BUCKETS (101)


typedef struct __hash_t {
    list_t lists[BUCKETS];
	pthread_mutex_t hlock;
}hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++) {
        List_Init(&H->lists[i]);
    }
	pthread_mutex_init(&H->hlock, NULL);
}

void *Hash_Insert(hash_t *H, int key) {
	pthread_mutex_lock(&H->hlock);
    int bucket = key % BUCKETS;
    List_Insert(&H->lists[bucket], key);
	pthread_mutex_unlock(&H->hlock);
}

void *Hash_Lookup(hash_t *H, int key) {
	pthread_mutex_lock(&H->hlock);
    int bucket = key % BUCKETS;
    List_Lookup(&H->lists[bucket], key);
	pthread_mutex_unlock(&H->hlock);
}
void *Hash_Delete(hash_t *H, int key){
	pthread_mutex_lock(&H->hlock);
    int bucket = key % BUCKETS;
    List_Delete(&H->lists[bucket], key);
	pthread_mutex_unlock(&H->hlock);
}


int main(int argc, char *argv[]){
	pthread_t thread_one;
	pthread_t thread_two;
	printf("Hello World\n");
    	hash_t myHash;
    	Hash_Init(&myHash);
pthread_create(&thread_one, NULL, Hash_Insert(&myHash, 10), NULL);
//pthread_create(&thread_one, NULL, Hash_Insert(&myHash, 7), NULL);
//pthread_create(&thread_one, NULL, Hash_Insert(&myHash, 9), NULL);

pthread_create(&thread_two, NULL, Hash_Insert(&myHash, 15), NULL);
//pthread_create(&thread_two, NULL, Hash_Insert(&myHash, 20), NULL);
//pthread_create(&thread_two, NULL, Hash_Insert(&myHash, 1), NULL);

Hash_Insert(&myHash, 7);Hash_Insert(&myHash, 9);
Hash_Insert(&myHash, 20);Hash_Insert(&myHash, 1);
    
    Hash_Delete(&myHash, 10);
    Hash_Delete(&myHash, 9);
    Hash_Delete(&myHash, 1);
    Hash_Delete(&myHash, 7);
    Hash_Lookup(&myHash, 9);
    Hash_Lookup(&myHash, 7);//works
    Hash_Lookup(&myHash, 10);
    Hash_Lookup(&myHash, 20);
    return 0;
}



