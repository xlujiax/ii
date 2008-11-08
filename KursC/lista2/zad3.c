// Maciej Pacut
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int m, n;

struct List
{
  struct List* tl;
  char* str;
};

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
      new_lst->str = old_lst->str;
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
      new_lst->str = hd->str;
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

struct List* read_lines()
{
  struct List* lines = 0;

  int sz; // unused
  
  while(1)
    {
      lines = concat(lines);
      
      if(-1 == getline(&lines->str, &sz, stdin))
	break;
    }
  return lines;
}


int lessThen(char* a, char* b)
{
  int i;
  for(i = m - 1; i < n; ++i)
    {
	if(a[i] < b[i])
	  return 1;
	if(a[i] > b[i])
	  return 0;
    }
  return 0;
}

int equalTo(char* a, char* b)
{
  int i;
  for(i = m - 1; i < n; ++i)
    {
	if(a[i] != b[i])
	  return 0;
    }
  return 1;
}

int greaterThen(char* a, char* b) // mozliwa implementacja: !equalTo && !lessThen
{
  int i;
  for(i = m - 1; i < n; ++i)
    {
	if(a[i] < b[i])
	  return 0;
	if(a[i] > b[i])
	  return 1;
    }
  return 0;
}

struct List* filter(struct List* hd, int (*fun)(char*, char*), char* param)
{
  struct List* old_lst = hd;
  struct List* new_lst = 0;
  while(old_lst)
    {
      if(fun(old_lst->str, param))
	{
	  new_lst = concat(new_lst);
	  new_lst->str = old_lst->str;
	}
      old_lst = old_lst->tl;
    }
  return new_lst;
}

void print_str(struct List* lst)
{
  printf("%s", lst->str);
}

void cleanup(struct List* lst)
{
  free(lst->str);
}

struct List* quicksort(struct List* lst)
{
  // []
  if(lst == 0)
    return 0;

  // [x]
  if(lst->tl == 0)
    return lst;

  // pivot:rest  
  char* pivot = lst->str;
  struct List* rest = lst->tl;
  
  struct List* before = filter(lst, lessThen, pivot);
  struct List* middle = filter(lst, equalTo, pivot);
  struct List* after = filter(lst, greaterThen, pivot);

  before = quicksort(before);
  after = quicksort(after);

  return append(before, append(middle, after));
}

int main(int argc, char *argv[])
{
  if(argc != 3)
    {
      printf("usage: zad3.e m n\n");
      return -1;
    }

  sscanf(argv[1], "%d", &m);
  sscanf(argv[2], "%d", &n);
  
  struct List* lines = read_lines();
  lines = quicksort(lines);
  iterate(lines, print_str);
  iterate(lines, cleanup);
  return 0;
}
