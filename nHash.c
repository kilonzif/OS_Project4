/**
@AUTHOR: Yamoah Bentil
FILE: normal hashtable

***/
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "nList.h"
#define BUCKETS (101)


typedef struct __hash_t {
    list_t lists[BUCKETS];
}hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++) {
        List_Init(&H->lists[i]);
    }
}

int Hash_Insert(hash_t *H, int key) {
    int bucket = key % BUCKETS;
    return List_Insert(&H->lists[bucket], key);
}

int Hash_Lookup(hash_t *H, int key) {
    int bucket = key % BUCKETS;
    return List_Lookup(&H->lists[bucket], key);
}
int Hash_Delete(hash_t *H, int key){
    int bucket = key % BUCKETS;
    return List_Delete(&H->lists[bucket], key);
}


int main(int argc, char *argv[]){
    printf("Hello World\n");
    hash_t myHash;
    Hash_Init(&myHash);
    Hash_Insert(&myHash, 10);
    Hash_Insert(&myHash, 1);
    Hash_Insert(&myHash, 7);
    Hash_Insert(&myHash, 9);
    Hash_Insert(&myHash, 15);
    Hash_Insert(&myHash, 20);
    Hash_Lookup(&myHash, 7);
    Hash_Delete(&myHash, 10);

    Hash_Lookup(&myHash, 9);
    Hash_Lookup(&myHash, 10);
    Hash_Lookup(&myHash, 20);
    return 0;
}



