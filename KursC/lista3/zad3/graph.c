// Maciej Pacut
#include "graph.h"

struct Graph* gCreate(int sz)
{
  struct Graph* g = malloc(sizeof(struct Graph));
  g->size = sz;
  g->adjMatrix = malloc(sz * sizeof(struct BitVector*));

  int i;
  for(i = 0; i < sz; ++i)
    g->adjMatrix[i] = bvCreate(sz);
  
  return g;
}
void gDestroy(struct Graph* g)
{
  int i;
  for(i = 0; i < g->size; ++i)
    bvDestroy(g->adjMatrix[i]);
  free(g->adjMatrix);
}

int gConnected(struct Graph* g, int i, int j)
{
  return bvRead(g->adjMatrix[i], j);
}

struct Graph* gRead()
{
  int sz;
  scanf("%d", &sz);
  struct Graph* g = gCreate(sz);

  int i, j;
  for(i = 0; i < sz; ++i)
    for(j = 0; j < sz; ++j)
      {
	int b;
	scanf("%d", &b);
	if(b)
	  bvOn(g->adjMatrix[i], j);
      }
  
  return g;
}

void gPrint(struct Graph* g)
{
  int i, j;
  for(i = 0; i < g->size; ++i)
    {
      for(j = 0; j < g->size; ++j)
	{
	  if(gConnected(g, i, j))
	    printf("1");
	  else
	    printf("0");
	}
      printf("\n");
    }
}

// depth first search
int gSizeOfComponent(struct Graph* g, struct BitVector* visited, int actual)
{
  bvOn(visited, actual);
  
  int sum = 1;
  int next;
  for(next = 0; next < g->size; ++next)
    if(gConnected(g, actual, next) && !bvRead(visited, next))
      sum += gSizeOfComponent(g, visited, next);
  return sum;
}

int gConnectedComponent(struct Graph* g)
{
  struct BitVector* visited = bvCreate(g->size);
  return g->size == gSizeOfComponent(g, visited, 0);
}

// do obliczenia najkrótszej ścieżki w grafie
// w którym każda krawędź ma wagę jednostkową
// wystarczy użyć algorytmu przeszukiwania
// opartego na kolejce (BFS)
// a nie jak w przypadku ogólnym - algorytmu
// opartego na kolejce priorytetowej (Dijkstra)
struct List* gShortestPath(struct Graph* g, int a, int b)
{
  struct Queue* q = quCreate(g->size);
  int* parents = malloc(g->size * sizeof(int));
  int i;
  for(i = 0; i < g->size; ++i)
    parents[i] = -1;

  enqueue(q, a);
  while(1)
    {
      if(quEmpty(q))
	printf("err: empty queue\n");

      int actual = dequeue(q);

      if(actual == b)
	break;

      int next;
      for(next = 0; next < g->size; ++next)
	if(gConnected(g, actual, next) && parents[next] == -1)
	  {
	    parents[next] = actual;
	    enqueue(q, next);
	  }
    }

  struct List* path = 0;
  int ptr = b;
  while(ptr != a)
    {
      path = concat(path);
      path->data = ptr;
      ptr = parents[ptr];
    }
  path = concat(path); // dodanie a
  path->data = ptr;

  free(parents);
  quDestroy(q);
  return path;
}
