// Maciej Pacut
#pragma once

#include <stdio.h>
#include "bitvector.h"
#include "list.h"
#include "queue.h"

struct Graph
{
  int size;
  struct BitVector** adjMatrix;
};

struct Graph* gCreate(int sz);
void gDestroy(struct Graph*);
int gConnectedComponent(struct Graph*);

struct Graph* gRead();
void gPrint(struct Graph* g);
int gConnected(struct Graph* g, int, int);

struct List* gShortestPath(struct Graph* g, int, int);
