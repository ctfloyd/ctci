#ifndef LINKEDLIST
#define LINKEDLIST

struct node_t {
    int data;
    struct node_t* next;
};

struct node_t* make_list(int length, int values[], int num_values);
void print_list(struct node_t* list);

#endif