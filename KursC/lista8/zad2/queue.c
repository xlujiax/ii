// Maciej Pacut
// lista 8 zad 2

#include "queue.h"

Queue* empty()
{
    Queue* q = malloc(sizeof(Queue));
    q->front = q->end = 0;
}

Queue* push_front(Queue* q, char* text)
{
    if(q->front == 0 && q->end == 0)
    {
        Node* n = malloc(sizeof(Node));
        n->prev = n->next = 0;
        n->data = text;
        
        q->front = q->end = n;
    }
    else
    {
        Node* n = malloc(sizeof(Node));
        n->prev = 0;
        n->next = q->front;
        n->data = text;
        
        q->front = n;
    }
}

char* pop_front(Queue* q)
{
    if(q->front == 0 && q->end == 0)
    {
        printf("err pop_front: queue is empty\n");
        return "\0";
    }
    else
    {
        char* tempData = q->front->data;
        Node* tempPtr = q->front->next;
        free(q->front);
        q->front = tempPtr;
        return tempData;
    }
}

Queue* push_back(Queue* q, char* text)
{
    if(q->front == 0 && q->end == 0)
    {
        Node* n = malloc(sizeof(Node));
        n->prev = n->next = 0;
        n->data = text;
        
        q->front = q->end = n;
    }
    else
    {
        Node* n = malloc(sizeof(Node));
        n->prev = q->end;
        n->next = 0;
        n->data = text;
        
        q->end = n;
    }
}

char* pop_back(Queue* q)
{
    if(q->front == 0 && q->end == 0)
    {
        printf("err pop_front: queue is empty\n");
        return "\0";
    }
    else
    {
        char* tempData = q->end->data;
        Node* tempPtr = q->end->next;
        free(q->end);
        q->end = tempPtr;
        return tempData;
    }
}
