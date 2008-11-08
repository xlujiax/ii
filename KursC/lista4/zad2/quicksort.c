#include "quicksort.h"

int lessThen(int a, int b)
{
    return a < b;
}

int equalTo(int a, int b)
{
  return a == b;
}

int greaterThen(int a, int b) // mozliwa implementacja: !equalTo && !lessThen
{
  return a > b;
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
  int pivot = lst->data;
  struct List* rest = lst->tl;
  
  struct List* before = filter(lst, lessThen, pivot);
  struct List* middle = filter(lst, equalTo, pivot);
  struct List* after = filter(lst, greaterThen, pivot);

  before = quicksort(before);
  after = quicksort(after);

  return append(before, append(middle, after));
}
