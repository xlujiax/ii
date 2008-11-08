// Maciej Pacut
// Lista 4
// Zad 3
#include "librarysort.h"

void Rebalance(GapArray* ga, float e)
{
  int oldSz = ga->sz;
  gExpand(ga, 2 * (oldSz + e));

  int taker = oldSz - 1;
  int inserter = 2 * oldSz - 1;
  while(taker >= 0)
    {
      if(!gIsGap(ga, taker))
	{
	  gSwap(ga, taker, inserter);
	  inserter -= 2;
	}
      
      taker--;
    }
}

int BinarySearch(GapArray* ga, int element, int left, int right)
{
  if(left == right)
    return left;

  if(left + 1 == right)
    {
      if(gIsGap(ga, left) && gIsGap(ga, right))
	return left;
      if(gIsGap(ga, left) && element <= gElement(ga, right))
	return left;
      return right;
    }

  int half = (left + right) / 2;

  if(gIsGap(ga, half)) // fix half
    if(half - 1 > left)
      half --;
    else if(half + 1 < right)
      half ++;
    else // no element in range [left..right]
	return left + 1;
  
  int midEl = gElement(ga, half);

  if(element == midEl)
    return half;

  if(element < midEl)
    return BinarySearch(ga, element, left, half);
  else
    return BinarySearch(ga, element, half, right);
}

void InsertToSorted(GapArray* ga, int element, int debug)
{
  if(debug)
    printf("InsertToSorted(%d)\n", element);
  int place = BinarySearch(ga, element, 0, ga->sz -1);

  if(debug)
    printf("Binary Search says %d\n", place);

  if(!gIsGap(ga, place))
    {
      if(element < gElement(ga, place))
	if(!gOutOfBounds(ga, gFirstGapRight(ga, place)))
	  { // common situation
	    gMoveRight(ga, place);
	    gInsert(ga, place, element);
	  }
	else
	  { // right is solid, so insert on the left
	    gMoveLeft(ga, place - 1);
	    gInsert(ga, place - 1, element);
	  }
      else
	if(!gOutOfBounds(ga, gFirstGapLeft(ga, place)))
	  {
	    gMoveLeft(ga, place);
	    gInsert(ga, place, element);
	  }
	else
	  {
	    gMoveLeft(ga, place + 1);
	    gInsert(ga, place + 1, element);
	  }
    }
  else
    gInsert(ga, place, element);
}

int* LibrarySort(int* arr, int sz, float e, int debug)
{
  GapArray* ga = gCreate(1, 2 * sz * (1 + e), -1); // (!) works only if -1 is not in given sequence

  int round = 0;
  int i;
  for(i = 0; i < sz; ++i)
    {
      if(debug)
	gPrintRaw(ga);

      if(i == (1 << round)) // 1 << x = 2^x
	{
	  Rebalance(ga, e);
	  if(debug)
	    {
	      printf("rebalance:\n");
	      gPrintRaw(ga);
	    }
	  ++round;
	}

      InsertToSorted(ga, arr[i], debug);
    }
  if(debug)
    gPrintRaw(ga);

  int* result = gToArray(ga);
  gDestroy(ga);
  return result;
}
