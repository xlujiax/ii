// Maciej Pacut
#pragma once
#include <malloc.h>

struct Queue
{
  int* data;
  int maxSize;
  int begin;
  int end;
};

struct Queue* quCreate(int maxSz);
void enqueue(struct Queue*, int el);
int dequeue(struct Queue*);
int quEmpty(struct Queue*);
void quDestroy(struct Queue*);
