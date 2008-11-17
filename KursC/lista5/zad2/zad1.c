// Maciej Pacut
// Lista 5
// zad 1

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int lessThen(double a, double b)
{
    return a < b;
}

int equalTo(double a, double b)
{
  return a == b;
}

int greaterThen(double a, double b) // mozliwa implementacja: !equalTo && !lessThen
{
  return a > b;
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
  int pivot = lst->data;
  struct List* rest = lst->tl;
  
  struct List* before = lFilter(lst, lessThen, pivot);
  struct List* middle = lFilter(lst, equalTo, pivot);
  struct List* after = lFilter(lst, greaterThen, pivot);

  before = lQuicksort(before);
  after = lQuicksort(after);

  return lAppend(before, lAppend(middle, after));
}

struct List* lInsertionsort(struct List* lst)
{
    struct List* acc = lEmpty();
    
    struct List* hd = lst;
    while(hd)
    {
        acc = lInsertToSorted(acc, hd->data);
        hd = hd->tl;
    }
    return acc;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    
    printf("losowo wygenerowana lista:\n");
    struct List* lst = lGenerate(5);
    lPrint(lst);
    
    printf("quicksort:\n");
    struct List* qsorted = lQuicksort(lst);
    lPrint(qsorted);
    
    printf("insertionsort:\n");
    struct List* insertionsorted = lInsertionsort(lst);
    lPrint(insertionsorted);
    
    lCleanup(lst);
    lCleanup(qsorted);
  
    system("PAUSE");	
    return 0;
}
