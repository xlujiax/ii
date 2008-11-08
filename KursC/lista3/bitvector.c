#include "bitvector.h"

// Maciej Pacut

struct BitVector* bvCreate(int sz)
{
  struct BitVector* s = malloc(sizeof(struct BitVector));
  s->size = sz;
  
  int cells = s->size / sizeof(cellType);
  int i;
  
  s->data = malloc(sizeof(cellType) * cells);

  for(i = 0; i < cells; ++i)
    s->data[i] = 0;

  return s;
}
void bvDestroy(struct BitVector* s)
{
  free(s->data);
}

void bvOn(struct BitVector* s, int index)
{
  s->data[index/sizeof(cellType)] |= (1 << index % sizeof(cellType));
}

void bvOff(struct BitVector* s, int index)
{
  s->data[index/sizeof(cellType)] &= ~(1 << index % sizeof(cellType));
}
int bvRead(struct BitVector* s, int index)
{
  return s->data[index/sizeof(cellType)] & (1 << index % sizeof(cellType));
}
