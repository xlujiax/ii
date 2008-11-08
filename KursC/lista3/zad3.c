// Maciej Pacut
#include <stdio.h>

#include "graph.h"
#include "list.h"
#include "queue.h"

int main()
{
  struct Graph* g = gRead();
  gPrint(g);
  printf("connected component? : %d\n", gConnectedComponent(g));

  int a, b;
  scanf("%d %d", &a, &b);
  struct List* path = gShortestPath(g, a, b);

  printf("shortest path from %d to %d is ", a, b);
  printList(path);

  gDestroy(g);
  
  return 0;
}
