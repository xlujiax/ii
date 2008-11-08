// Maciej Pacut
#include "list.h"

struct List* concat(struct List* old_head)
{
  struct List* new_head = malloc(sizeof(struct List));
  new_head->tl = old_head;
  return new_head;
}

void iterate(struct List* lst, void (*fun)(struct List*))
{
  struct List* hd = lst;
  while(hd)
    {
      fun(hd);
      hd = hd->tl;
    }
}

void printNumber(struct List* lst)
{
  printf("%d ", lst->data);
}
void printList(struct List* lst)
{
  printf("[ ");
  iterate(lst, printNumber);
  printf("]\n");
}
