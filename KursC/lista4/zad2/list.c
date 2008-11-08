#include "list.h"

struct List* concat(struct List* old_head)
{
  struct List* new_head = malloc(sizeof(struct List));
  new_head->tl = old_head;
  return new_head;
}

struct List* reverse(struct List* hd)
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      new_lst = concat(new_lst);
      new_lst->data = old_lst->data;
      old_lst = old_lst->tl;
    }
  return new_lst;
}

struct List* append(struct List* a, struct List* b)
{
  struct List* new_lst = b;
  struct List* hd = reverse(a);
  while(hd)
    {
      new_lst = concat(new_lst);
      new_lst->data = hd->data;
      hd = hd->tl;
    }
  return new_lst;
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

struct List* filter(struct List* hd, int (*fun)(int, int), int param)
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      if(fun(old_lst->data, param))
	{
	  new_lst = concat(new_lst);
	  new_lst->data = old_lst->data;
	}
      old_lst = old_lst->tl;
    }
  return new_lst;
}

void print_int(struct List* lst)
{
  printf("%d ", lst->data);
}

void cleanup(struct List* lst)
{
  free(lst);
}

void print_list(struct List* lst)
{
     printf("[");
  iterate(lst, print_int);
     printf("]\n");
}
struct List* generate_lst(int sz)
{
 struct List* lines = 0;

  int i;
  for(i = 0; i < sz; ++i)
    {
      lines = concat(lines);
      lines->data = rand();
    }
  return lines;
}
