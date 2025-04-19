#include "graph.h"

dnode* head, * tail;



void init_queue()
{
    head = (dnode*)calloc(1, sizeof(dnode));
    tail = (dnode*)calloc(1, sizeof(dnode));
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
}


//put 'k' data infront of tail
int put(int k)
{
    dnode* t;
    if ((t = (dnode*)malloc(sizeof(dnode))) == NULL){
        printf("Out of memory !\n");
        return -1;
    }
    t->key = k;
    tail->prev->next = t;
    t->prev = tail->prev;
    tail->prev = t;
    t->next = tail;
    return k;
}


int get()
{
    dnode* t;
    int k;
    t = head->next;
    if (t == tail){
        printf("Queue underflow\n");
        return -1;
    }
    k = t->key;
    head->next = t->next;
    t->next->prev = head;
    free(t);
    return k;
}


int queue_empty()
{
    if (head->next == tail) return 1;
    else return 0;
}