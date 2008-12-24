// Maciej Pacut
#include "queue.h"

struct Queue* quCreate(int maxSz)
{
  struct Queue* q = malloc(sizeof(struct Queue));
  q->maxSize = maxSz;
  q->data = malloc(maxSz * sizeof(int));
  q->begin = q->end = 0;
  return q;
}
void enqueue(struct Queue* q, int el)
{
  q->data[q->end] = el;
  ++q->end;
  if(q->end == q->maxSize)
    q->end = 0;
}
int dequeue(struct Queue* q)
{
  int temp_begin = q->begin;
  ++q->begin;
  if(q->begin == q->maxSize)
    q->begin = 0;

  return q->data[temp_begin];
}
int quEmpty(struct Queue* q)
{
  return q->begin == q->end;
}
void quDestroy(struct Queue* q)
{
  free(q->data);
  free(q);
}
