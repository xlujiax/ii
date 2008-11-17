// Maciej Pacut
// Lista 5
// zad 1
#include "list.h"

struct List* lEmpty()
{
    return 0;
}

int lLength(struct List* lst)
{
    int len = 0;
    struct List* hd = lst;
    while(hd)
    {
        ++len;
        hd = hd->tl;
    }
    return len;
}

struct List* lConcat(struct List* old_head, LST_TYPE val)
{
  struct List* new_head = malloc(sizeof(struct List));
  new_head->tl = old_head;
  new_head->data = val;
  return new_head;
}

struct List* lReverse(struct List* hd)
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      new_lst = lConcat(new_lst, old_lst->data);
      old_lst = old_lst->tl;
    }
  return new_lst;
}

struct List* lCopy(struct List* hd)
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      new_lst = lConcat(new_lst, old_lst->data);
      old_lst = old_lst->tl;
    }
  return lReverse(new_lst);
}

struct List* lAppend(struct List* a, struct List* b)
{
  struct List* new_lst = b;
  struct List* hd = lReverse(a);
  while(hd)
    {
      new_lst = lConcat(new_lst, hd->data);
      hd = hd->tl;
    }
  return new_lst;
}

void lIterate(struct List* lst, void (*fun)(struct List*))
{
  struct List* hd = lst;
  while(hd)
    {
      fun(hd);
      hd = hd->tl;
    }
}

struct List* lFilter(struct List* hd, int (*fun)(LST_TYPE, LST_TYPE), LST_TYPE param) // param to symulacja closures w C
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      if(fun(old_lst->data, param))
	{
	  new_lst = lConcat(new_lst, old_lst->data);
	}
      old_lst = old_lst->tl;
    }
  return lReverse(new_lst);
}

void print_int(struct List* lst)
{
  printf("%2.1f ", lst->data);
}

void lCleanup(struct List* lst)
{
  free(lst);
}

void lPrint(struct List* lst)
{
     printf("[");
  lIterate(lst, print_int);
     printf("]\n");
}
struct List* lGenerate(int sz)
{
 struct List* lines = 0;

  int i;
  for(i = 0; i < sz; ++i)
    {
      lines = lConcat(lines, rand() % 10);
    }
  return lines;
}


struct List* lAddToTail(struct List* lst, LST_TYPE val)
{
    struct List* hd = lCopy(lst);
    while(1)
    {
        if(!hd->tl)
        {
            hd->tl = malloc(sizeof(struct List));
            hd->tl->tl = lEmpty();
            hd->tl->data = val;
            return;
        }
        hd = hd->tl;
    }
}

int lLess(LST_TYPE a, LST_TYPE b)
{
    return a < b;
}

int lGreaterOrEqual(LST_TYPE a, LST_TYPE b)
{
    return a >= b;
}

struct List* lInsertToSorted(struct List* lst, LST_TYPE val)
{
    return lAppend(lFilter(lst, lLess, val), lConcat(lFilter(lst, lGreaterOrEqual, val), val));
}
