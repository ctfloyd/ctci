// Write code to remove duplicates from an unsorted linked list.
// Follow up: How would you solve this problem if a temporary buffer is not allowed?
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../../util/linkedlist.h"

struct hashnode_t {
    int key;
    int value;
    struct hashnode_t* next;
};

struct hashtable_t {
    struct hashnode_t** array;
    int size;
};

int get_hash(struct hashtable_t* ht, int key) {
    return key % ht->size;
}

struct hashnode_t* lookup(struct hashtable_t* ht, int key) {
    struct hashnode_t* bucket = ht->array[get_hash(ht, key)];
    if(!bucket)
        return NULL;
    if(bucket->key == key)
        return bucket;
    while(bucket->next) {
        if(bucket->key == key)
            return bucket;
        bucket = bucket->next;
    }
    return NULL;
}

/*
   Inserts a new key, value pair into a hashtable.
   Returns 0 on success
   Returns -1 if there was an error
*/
int insert(struct hashtable_t* ht, int key, int value) {
    struct hashnode_t* bucket = lookup(ht, key);
    int hash = get_hash(ht, key);

    struct hashnode_t* new_node = malloc(sizeof(struct hashnode_t));
    if(!new_node) {
        return -1;
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    if(!bucket) {
        ht->array[hash] = new_node;
        return 0;
    }

    while(bucket->next) {
        bucket = bucket->next;
    }

    bucket->next = new_node;
    return 0;
}

/*
    Makes a hash table with desired size. Fills the table with NULL.
    Returns the created hashtable, NULL on error.
*/
struct hashtable_t* make_hashtable(int size) {
    struct hashtable_t* table = malloc(sizeof(struct hashtable_t));
    if(!table) {
        return NULL;
    }
    table->size = size;
    table->array = malloc(size * sizeof(struct hashnode_t*));
    if(!table->array) {
        free(table);
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        table->array[i] = NULL;
    }
    return table;
}


// Removes duplicate values from a linked list
// Returns 0 on success, -1 otherwise
// This implemenation's run time: O(N), space: O(N);
int remove_duplicates_ht(struct node_t* list) {
    if(!list) {
        return 0;
    }

    struct hashtable_t* map = make_hashtable(100);
    if(!map) {
        printf("An unexpected error has occured..\n");
        return -1;
    }

    struct node_t* current = list;
    struct node_t* previous = list;
    while(current->next) {
        struct hashnode_t* exists = lookup(map, current->data);
        if(!exists) {
            insert(map, current->data, 1);
            previous = current;
            current = current->next;
        } else {
            struct node_t* free_node = current;
            previous->next = current->next;
            current = current->next;
            free(free_node);
        }
    }
    return 0;
}

/*
   Removes duplicate values from a linked list
   returns 0 on success, -1 otherwise
   This implementation takes: O(N^2) time, and O(1) space
*/
int remove_duplicates_inline(struct node_t* list) {
    if(!list || !list->next) {
        return 0;
    }
    struct node_t* current = list;
    struct node_t* runner = list;
    while(current->next) {
        while(runner->next) {
            if(runner->next->data == current->data) {
                struct node_t* free_node = runner->next;
                runner->next = runner->next->next;
                free(free_node);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
        runner = current;
    }
    return 0;
}
int main() {
    int list_length = 50000;
    int num_values = 28;
    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 };
    struct node_t* list1 = make_list(list_length, values, num_values);
    struct node_t* list2 = make_list(list_length, values, num_values);
//    printf("Original list: ");
 //   print_list(list1);
    printf("\nRemoving duplicates using hashtable.\n");
    clock_t begin = clock();
    remove_duplicates_ht(list1);
    clock_t end = clock();
  //  print_list(list1);
    printf("\nBenchmark: %f", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("\nRemoving duplicates using inline runner.\n");
    begin = clock();
    remove_duplicates_inline(list2);
    end = clock();
//    print_list(list2);
    printf("\nBenchmark: %f", (double)(end - begin) / CLOCKS_PER_SEC);
    printf("\n");
}
