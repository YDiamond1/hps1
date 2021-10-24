
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


node_t* create_node(int val){
    node_t * node = malloc(sizeof (node_t));
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

node_t* next(node_t* list){
    if(list != NULL){
        return list->next;
    }
    return NULL;
}

node_t * get_node_t(linked_list * list, int i){
    if(i >= 0){
        node_t * iter = list->head;
        int j = 0;
        while(j++ < i && iter != NULL) iter = next(iter);
        return iter;
    }else{
        node_t * iter = list->tail;
        int j = -1;
        while(j-- > i && iter != NULL) iter = iter->prev;
        return iter;
    }
}



node_t* get_last(node_t* list){
    node_t * iter = list;
    while (iter->next != NULL) iter = iter->next;
    return iter;
}

void change(linked_list* list, int i, int val){
    node_t * iter = get_node_t(list, i);
    if(iter != NULL)
        iter->val = val;
}

void append_linked_list(linked_list* list, int val){
    if(list != NULL && list->heap_size > 0){
        append(&(list->tail), val);
        list->tail = list->tail->next;
        list->heap_size += 1;
    }else{
        append(&(list->head), val);
        list->tail = list->head;
        list->heap_size+=1;
    }
}

int pop(linked_list* list){
    int ret = list->tail->val;
    node_t *delete = list -> tail;
    list->tail = list->tail->prev;
    free(delete);
    if(list->tail != NULL)
        list->tail->next = NULL;
    else
        list->head = NULL;
    list->heap_size -= 1;
    return ret;
}

int get_linked_list(linked_list* list, int i){
    return get_node_t(list, i)->val;
}

void append(node_t** list, int append){
    if(*list != NULL){
        node_t* last = get_last(*list);
        last->next = create_node(append);
        last->next->prev = last;
    }else{
        *list = create_node(append);
    }
}

int get(node_t* list, int i){
    node_t * iter = list;
    int j = 0;
    while(j++ < i && iter != NULL) iter = next(iter);
    if(iter != NULL) {
        return iter->val;
    }
    else{
        exit(-666);
    }

}

void free_list(node_t** list){
    if(*list != NULL){
        node_t * iter = *list;
        while(iter != NULL){
            node_t * free_element = iter;
            iter = free_element->next;
            free(free_element);
        }
        *list = NULL;
    }
}

void print_list(node_t* list){
    node_t * iter = list;
    while(iter != NULL){
        printf("%d ", iter->val);
        iter = iter->next;
    }
}

int contains(node_t* list, int val){
    node_t * iter = list;
    int i = 0;
    while(iter != NULL && iter->val != val) {iter = iter->next; i++;}
    if(iter == NULL){
        return -1;
    }
    return i;
}

void swap(int* first, int *second){
    int tmp = *first;
    *first = *second;
    *second = tmp;
}