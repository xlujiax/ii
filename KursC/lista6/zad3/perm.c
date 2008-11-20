#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


int factorial(int n)
{
  int res = 1;
  int i;
  for(i = 1; i <= n; ++i)
    res *= i;
  return res;
}

int size;
int* arr;
int* walker;

int* used;

void print_arr(int* arr, int size)
{
  int i;
  for(i = 0; i < size; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

int equal_arr(int* a, int* b, int size)
{
  int i;
  for(i = 0; i < size; ++i)
    if(a[i] != b[i])
      return 0;
  return 1;
}

int** perms;
int inserter;

void copy_arr(int* src, int* dest, int size)
{
  int i;
  for(i = 0; i < size; ++i)
    dest[i] = src[i];
}

void store_arr(int* arr, int size)
{
  copy_arr(arr, perms[inserter++], size);
}

void permutations(int level)
{
  if(level == size)
    {
      //print_arr(walker, size);
      store_arr(walker, size);
    }
  else
    {
      int i;
      for(i = 0; i < size; ++i)
	{
	  if(used[i])
	    continue;
	  
	  walker[level] = arr[i];
	  used[i] = 1;
	  
	  permutations(level + 1);

	  used[i] = 0;
	}
    }
}

// uzywa zmiennej globalnej size
int arr_cmp(const void *a, const void *b)
{
  const int *arr1 = *((const int*)a);
  const int *arr2 = *((const int*)b);
  int i;
  for(i = 0; i < size; ++i)
    {
      if(arr1[i] < arr2[i])
	return -1;
      else if(arr1[i] > arr2[i])
	return 1;
    }
  return 0;
}


void print_perms_unique()
{
  qsort(perms, factorial(size), sizeof(int*), arr_cmp);

  
  print_arr(perms[0], size);
  int i;
  for(i = 1; i < factorial(size); ++i)
    if(!equal_arr(perms[i - 1], perms[i], size))
       print_arr(perms[i], size);
}

int main()
{
  int i;
  scanf("%d", &size);
  arr = malloc(sizeof(int) * size);
  walker = malloc(sizeof(int) * size);
  
  perms = malloc(sizeof(int*) * factorial(size));
  for(i = 0; i < factorial(size); ++i)
    perms[i] = malloc(sizeof(int) * size);
  
  used = malloc(sizeof(int) * size);

  for(i = 0; i < size; ++i)
    used[i] = 0;

  for(i = 0; i < size; ++i)
    scanf("%d", &arr[i]);
  printf("--------\n");

  permutations(0);
  print_perms_unique();
  
  return 0;
}
