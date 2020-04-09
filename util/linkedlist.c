#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
    Returns a list with values populated by given array.
    Returns NULL, when it is unable to allocated memory for a list at all.
    If a partial list is constructed before the system runs out of memory,
    then the partial list will be returned. It is up to the caller to check
    the length of the list and free the memory.
*/
struct node_t* make_list(int length, int values[], int num_values) {
    struct node_t* list = malloc(sizeof(struct node_t));
    list->data = -1;
    list->next = NULL;
    if(!list)
        return NULL;
    struct node_t* current = list;
    srand(time(NULL));
    for(int i = 0; i < length; i++) {
        current->data = rand() % (length - 1);
        current->next = malloc(sizeof(struct node_t));
        if(!current->next)
            return list;
        current = current->next;
    }
    return list;
}

void print_list(struct node_t* list) {
    printf("%s", "[");
    while(list->next) {
        if(list->next->next)
            printf("%d, ", list->data);
        else printf("%d", list->data);
        list = list->next;
    }
    printf("%s", "]");
}