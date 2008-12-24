// Maciej Pacut
// lista 8 zad 2

#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef struct NodeSelf {
    char* data;
    struct NodeSelf* prev;
    struct NodeSelf* next;
} Node;

typedef struct QueueSelf {
    Node* front;
    Node* end;
} Queue;

Queue* empty();
Queue* push_front(Queue* q, char* text);
char* pop_front(Queue* q);
Queue* push_back(Queue* q, char* text);
