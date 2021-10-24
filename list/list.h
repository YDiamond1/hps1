//
// Created by YDiamond on 10.10.2021.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H

typedef struct node{
    int val;
    struct node* next;
    struct node* prev;
} node_t;

typedef struct {
    node_t * head;
    node_t * tail;
    int heap_size;
} linked_list;

enum get{
    SUCCESS,
    FAIL
};

void append_linked_list(linked_list* list, int append);

int get_linked_list(linked_list* list, int val);

int pop(linked_list* list);

void append(node_t** list, int append);

int contains(node_t* list, int val);

int get(node_t* list, int i);

void free_list(node_t** list);

void print_list(node_t* list);

void change(linked_list* list, int i, int val);

void swap(int* first, int *second);

#endif //LAB1_LIST_H
