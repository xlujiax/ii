#include "ncs.h"

ncs* ncs_create(control* c)
{
  ncs* n = malloc(sizeof(ncs));
  n->c = c;
  ncs_recalc(n);
  return n;
}

void ncs_recalc(ncs* n)
{
}
