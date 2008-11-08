// Maciek Pacut
#pragma once

#include <malloc.h>
#include <stdio.h>
// Maciej Pacut
// Lista 4
// Zad 3
#include <stdlib.h>

typedef struct
{
  int* arr;
  int maxSz;
  int sz;
  int GAP;
} GapArray;

GapArray* gCreate(int sz, int maxSz, int GAP);
void gDestroy(GapArray* ga);
void gPrint(GapArray* ga);
void gPrintRaw(GapArray* ga);

void gInsert(GapArray* ga, int index, int element);

int  gIsGap(GapArray* ga, int place);
int  gElement(GapArray* ga, int place);

int  gFirstGapRight(GapArray* ga, int start); // start = gap => start
int  gFirstGapLeft(GapArray* ga, int start);
int  gFirstElementRight(GapArray* ga, int start);
int  gFirstElementLeft(GapArray* ga, int start);
int  gOutOfBounds(GapArray* ga, int index); // boolean, bounds ~ actual size, not max size

void gSwap(GapArray* ga, int a, int b);
void gMoveLeft(GapArray* ga, int start); // moves till gap
void gMoveRight(GapArray* ga, int start); // moves till gap

void gExpand(GapArray* ga, int newSize);
