// Maciej Pacut
// Lista 5
// zad 1
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#define LST_TYPE double

struct List
{
  struct List* tl;
  LST_TYPE data;
};

struct List*    lEmpty(); // O(1)
int             lLength(struct List*); // O(n)
struct List*    lConcat(struct List* old_head, LST_TYPE val); // O(1)
struct List*    lReverse(struct List* hd); // O(n)
struct List*    lAppend(struct List* a, struct List* b); // O(n)
void            lIterate(struct List* lst, void (*fun)(struct List*)); // O(n)
struct List*    lFilter(struct List* hd, int (*fun)(LST_TYPE, LST_TYPE), LST_TYPE); // O(n)
void            lPrint(struct List* lst); // O(n)
void            lCleanup(struct List* lst); // O(n)
struct List*    lCopy(struct List* hd); // O(n)
struct List*    lAddToTail(struct List*, LST_TYPE); // O(n)

struct List*    lGenerate(int sz); // O(n)

int             lLess(LST_TYPE, LST_TYPE);
int             lGreaterOrEqual(LST_TYPE, LST_TYPE);
struct List*    lInsertToSorted(struct List* lst, LST_TYPE val); // O(n)
