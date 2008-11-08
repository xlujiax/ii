// Maciej Pacut
// Lista 4
// Zad 3
#include <stdio.h>

#include "gaparray.h"
#include "librarysort.h"
#include "sorttest.h"

float e;
int debug = 0;

int* librarySortWrapper(int* arr, int sz)
{
  return LibrarySort(arr, sz, e, debug);
}

int main()
{
  srand(time(0));
  printf("library sort test; choose:\n1. enter your sequence to sort\n2. check times\nanything else to quit\n");
  int choice;
  scanf("%d", &choice);
  switch(choice)
    {
    case 1:
      {
	debug = 1;

	printf("enter E: ");
	scanf("%f", &e);

	int sz;
	printf("enter length of sequence: ");
	scanf("%d", &sz);
	printf("enter %d number separated by space: ", sz);

	int* arr;
	arr = malloc(sz * sizeof(int));

	int i;
	for(i = 0; i < sz; ++i)
	  scanf("%d", &arr[i]);

	int* result = librarySortWrapper(arr, sz);
	for(i = 0; i < sz; ++i)
	  printf("%d ", result[i]);
	printf("\n");
      }
      break;
    case 2:
      {
	printf("enter E: ");
	scanf("%f", &e);
	
	printf("enter size of sequence: ");
	int sz;
	scanf("%d", &sz);
	
	printf("enter number of trials: ");
	int t;
	scanf("%d", &t);

	printf("sec: %f\n", average_time(librarySortWrapper, sz, t));
      }
      break;
    }
  return 0;
}
