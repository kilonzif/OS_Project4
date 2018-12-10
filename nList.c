/**
@AUTHOR: Wayne Gakuo
FILE: normal linkedlist

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
}list_t;

void List_Init(list_t *L) {
    L->head = NULL;
}
int List_Insert(list_t *L, int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return -1;
    }
    new->key = key;
    new->next = L->head;
    L->head = new;
    return 0;
}
int List_Lookup(list_t *L, int key) {
    int rv = -1;
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            printf("%d",curr->key);
            printf("\n");
            rv = 0;
        }
        curr = curr->next;
    }
    return rv; // now both success and failure
}

int List_Delete(list_t *L, int key){
    node_t *curr = L->head;
    node_t *prev = NULL;

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
        free (curr);
        return key;
    }
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
	printf("Hello World\n");
    	list_t myList;
    	List_Init(&myList);
    	List_Insert(&myList, 10);
    	List_Insert(&myList, 12);
    	List_Insert(&myList, 13);
    	List_Insert(&myList, 14);
    	List_Insert(&myList, 15);
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

 