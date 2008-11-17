// Maciej Pacut
// Lista 5
// zad 1

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int lessThen(char* a, char* b)
{
  int i;
  for(i = 0; i < strlen(a); ++i)
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
  for(i = 0; i < strlen(a); ++i)
    {
  if(a[i] != b[i])
   return 0;
    }
  return 1;
}
 
int greaterThen(char* a, char* b) // mozliwa implementacja: !equalTo && !lessThen
{
  int i;
  for(i = 0; i < strlen(a); ++i)
    {
  if(a[i] < b[i])
   return 0;
  if(a[i] > b[i])
   return 1;
    }
  return 0;
}

struct List* lQuicksort(struct List* lst)
{
  // []
  if(lst == 0)
    return 0;

  // [x]
  if(lst->tl == 0)
    return lst;

  // pivot:rest  
  char* pivot = lst->data;
  struct List* rest = lst->tl;
  
  struct List* before = lFilter(lst, lessThen, pivot);
  struct List* middle = lFilter(lst, equalTo, pivot);
  struct List* after = lFilter(lst, greaterThen, pivot);

  before = lQuicksort(before);
  after = lQuicksort(after);

  return lAppend(before, lAppend(middle, after));
}

int main(int argc, char *argv[])
{
    struct List* lst = lReadLines();
    
    lst = lQuicksort(lst);
    lPrint(lst);
    
    lCleanup(lst);
  
    system("PAUSE");	
    return 0;
}
