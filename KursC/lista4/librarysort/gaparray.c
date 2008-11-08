// Maciej Pacut
// Lista 4
// Zad 3
#include "gaparray.h"

GapArray* gCreate(int sz, int maxSz, int GAP)
{
  GapArray* ga = malloc(sizeof(GapArray));
  ga->sz = sz;
  ga->maxSz = maxSz;
  ga->GAP = GAP;
  ga->arr = malloc(maxSz * sizeof(int));
  
  int i;
  for(i = 0; i < maxSz; ++i)
    ga->arr[i] = GAP;

  return ga;
}
void gDestroy(GapArray* ga)
{
  free(ga->arr);
  free(ga);
}
int* gToArray(GapArray* ga)
{
  int* result = malloc(ga->sz * sizeof(int));
  int i;
  int inserter = 0;
  for(i = 0; i < ga->maxSz; ++i)
    if(!gIsGap(ga, i))
      {
	result[inserter] = gElement(ga, i);
	++inserter;
      }
  return result;
}
void gPrint(GapArray* ga)
{
  int i;
  printf("[ ");
  for(i = 0; i < ga->sz; ++i)
    if(!gIsGap(ga, i))
      printf("%d ", ga->arr[i]);
  printf("]\n");
}
void gPrintRaw(GapArray* ga)
{
  int i;
  printf("{ ");
  for(i = 0; i < ga->sz; ++i)
    if(!gIsGap(ga, i))
      printf("%d ", ga->arr[i]);
    else
      printf("- ");
  printf("}\n");
}

void gInsert(GapArray* ga, int index, int element)
{
  if(index < 0 || index > ga->maxSz)
    {
      printf("*** error: gInsert(index = %d, element = %d) inserts out of physical bounds ***\n", index, element);
      exit(-1);
    }
  else if(index > ga->sz)
    printf("*** warning: gInsert(index = %d, element = %d) inserts out of actual size (%d) ***\n", index, element, ga->sz);

  if(!gIsGap(ga, index))
    printf("*** warning: gInsert(index = %d, element = %d) replaces existing element %d ***\n", index, element, ga->arr[index]);

  ga->arr[index] = element;
}
int  gElement(GapArray* ga, int place)
{
  if(gIsGap(ga, place))
    printf("*** warning: gElement(place = %d) is a gap ***\n", place);
  else
    return ga->arr[place];
}

int  gIsGap(GapArray* ga, int place)
{
  return ga->arr[place] == ga->GAP;
}
int  gFirstGapRight(GapArray* ga, int start)
{
  int i;
  for(i = start; i < ga->maxSz; ++i)
    if(gIsGap(ga, i))
      return i;
  return ga->maxSz;
}

int  gFirstGapLeft(GapArray* ga, int start)
{
  int i;
  for(i = start; i > -1; --i)
    if(gIsGap(ga, i))
      return i;
  return -1;
}
int  gFirstElementRight(GapArray* ga, int start)
{
  int i;
  for(i = start; i < ga->maxSz; ++i)
    if(!gIsGap(ga, i))
      return i;
  return ga->maxSz;
}

int  gFirstElementLeft(GapArray* ga, int start)
{
  int i;
  for(i = start; i > -1; --i)
    if(!gIsGap(ga, i))
      return i;
  return -1;
}

int  gOutOfBounds(GapArray* ga, int index)
{
  return index < 0 || index >= ga->sz;
}

void gSwap(GapArray* ga, int a, int b)
{
  if(gOutOfBounds(ga, a))
    {
      printf("*** error: gSwap(a = %d, b = %d) a out of bounds ***\n", a, b);
      exit(-1);
    }
  if(gOutOfBounds(ga, b))
    {
      printf("*** error: gSwap(a = %d, b = %d) b out of bounds ***\n", a, b);
      exit(-1);
    }
  int t = ga->arr[a];
  ga->arr[a] = ga->arr[b];
  ga->arr[b] = t;
}

void gMoveRight(GapArray* ga, int start)
{
  int end = gFirstGapRight(ga, start);
  if(gOutOfBounds(ga, end))
    {
      printf("*** error: gMoveRight(start = %d) cannot move - no gap on the right ***\n", start);
      exit(-1);
    }
  if(end == start)
    printf("*** warning: gMoveRight(start = %d) move starts from gap - zero elements moved ***\n", start);

  int i;
  for(i = end; i > start; --i) // reverse moving, no temp array
    gSwap(ga, i, i - 1);
}

void gMoveLeft(GapArray* ga, int start)
{
  int end = gFirstGapLeft(ga, start);
  if(gOutOfBounds(ga, end))
    {
      printf("*** error: gMoveLeft(start = %d) cannot move - no gap on the left ***\n", start);
      exit(-1);
    }
  if(end == start)
    printf("*** warning: gMoveLeft(start = %d) move starts from gap - zero elements moved ***\n", start);

  int i;
  for(i = end; i < start; ++i) // reverse moving, no temp array
    gSwap(ga, i, i + 1);
}

void gExpand(GapArray* ga, int newSz)
{
  if(newSz > ga->maxSz)
    {
      printf("*** error: Rebalance from size %d to %d exceeds physical array size %d ***\n", ga->sz, newSz, ga->maxSz);
      exit(-1);
    }
  // expand
  ga->sz = newSz;
}
