#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../../../util/linkedlist.h"

int kth_element_r(struct node_t* list, int k) {
    if(!list)
        return 0;
    struct node_t* current = list;
    int count = kth_element_r(current->next, k) + 1;
    if(count == k + 1) {
        printf("%dth to last node is %d\n", k, current->data);
    }
    return count;
}

int kth_element_i(struct node_t* list, int k) {
    struct node_t* head = list;
    struct node_t* runner = list;
    for(int i = 0; i <= k; i++) {
        if(!runner) return 0;
        runner = runner->next;
    }
    while(runner != NULL) {
        head = head->next;
        runner = runner->next;
    }
    printf("%dth to last node is %d\n", k, head->data);
    return k;
}

// Implement an algorithm to find the kth to last element of a singly linked list.
// 2 options here: iterative vs recursive
int main() {
    int list_length = 10;
    int num_values = 10;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    struct node_t* list1 = make_list(list_length, values, num_values);
    print_list(list1);
    printf("\n");
    clock_t begin = clock();
    kth_element_r(list1, 1);
    clock_t end = clock();
    printf("Benchmark: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
    begin = clock();
    kth_element_i(list1, 1);
    end = clock();
    printf("Benchmark: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
}
