#include <stdio.h>
#include <stdlib.h>

#include "sorttest.h"

// dla wrappera qsort
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
// wrapper dla qsort
void qsort_std(int* arr, int sz)
{
     qsort(arr, sz, sizeof(int), compare);
}

void pr(int* arr, int sz)
{
 printf("[");
 int j;
 for(j = 0; j < sz; ++j)
       printf("%d ", arr[j]);
 printf("]\n");
}

int* cpy(int* arr, int sz)
{
 int* n = malloc(sizeof(int) * sz);
 int j;
 for(j = 0; j < sz; ++j)
       n[j] = arr[j];
 return n;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int* arr = generate(10);
    int* arr2 = cpy(arr, 10);
 printf("generowanie losowej sekwencji 10 liczb:\n"); pr(arr, 10);
 qsort_std(arr, 10);
 printf("sortowanie w/w sekwencji 10 liczb:\n"); pr(arr, 10);
 printf("czy ten algorytm posortowa³ poprawnie? %d\n", sortedp(arr, 10));
 printf("czy sekwencja wynikowa jest permutacj¹sekwencji wejsciowej? %d\n", permp(arr, arr2, 10));
 
 free(arr);
  printf("sredni czas sortowania 1000 elementow (10000 prob): %f\n", average_time(qsort_std, 1000, 10000));
  system("PAUSE");
  return 0;
}
