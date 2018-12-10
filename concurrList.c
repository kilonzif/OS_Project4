/**
@AUTHOR: Wayne Gakuo
FILE: concurrent linkedlist

***/
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 


// basic node structure
typedef struct __node_t{
    int key;
    struct __node_t *next;}node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
}list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}
void *List_Insert(list_t *L, int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
	exit(0);
    }
    new->key = key;
    // just lock critical section
    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
}
int List_Lookup(list_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            printf("%d",curr->key);
            printf("\n");
            rv = 0;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

int List_Delete(list_t *L, int key){
    node_t *curr = L->head;
    node_t *prev = NULL;
    pthread_mutex_lock(&L->lock);

    while(curr->key !=key && curr->next !=NULL){
        prev=curr;
        curr=curr->next;
    }
    if (curr->key == key){
        if (prev){
            prev->next = curr->next;
        }
        else {
            L->head = curr->next;
        }
        pthread_mutex_unlock(&L->lock);
        free (curr);
        return key;
    }
    pthread_mutex_unlock(&L->lock);
    return -1;
}

int printList(list_t *L){
	node_t *curr = L->head;
	
	while(curr){
		printf("%d", curr->key);
		printf("\n");
		curr = curr->next;
	}
	return 0;
}

int main(int argc, char *argv[]){
	pthread_t thread_one;
	pthread_t thread_two;
	printf("Hello World\n");
    	list_t myList;
    	List_Init(&myList);

pthread_create(&thread_one, NULL, List_Insert(&myList, 10), NULL);
pthread_create(&thread_one, NULL, List_Insert(&myList, 13), NULL);
pthread_create(&thread_one, NULL, List_Insert(&myList, 14), NULL);

pthread_create(&thread_two, NULL, List_Insert(&myList, 12), NULL);
pthread_create(&thread_two, NULL, List_Insert(&myList, 15), NULL);

	printList(&myList);
	printf("before delete\n");
    	//List_Delete(&myList, 13);// delete this
	List_Delete(&myList, 10);
	List_Delete(&myList, 12);
    printf("check if 13 is present in the list \n");
    List_Lookup(&myList, 13);// check if delete
    printf("check if 10 is present in the list \n");
    List_Lookup(&myList, 10);//check if 10 exists
    printf("Printing list items \n");
	printList(&myList);
	return 0;
}

 
