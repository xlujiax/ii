// Maciej Pacut
// uproszczona implementacja wektora bitów

#pragma once

#include <malloc.h>

typedef int cellType;
struct BitVector
{
  int size;
  cellType* data;
};

struct BitVector* bvCreate(int sz);
void bvDestroy(struct BitVector*);
void bvOn(struct BitVector*, int index);
void bvOff(struct BitVector*, int index);
int bvRead(struct BitVector*, int index);
