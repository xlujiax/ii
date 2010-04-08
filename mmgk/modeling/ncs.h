#ifndef NCS_H
#define NCS_H

#include "control.h"

typedef struct
{
  control* c;
  float* M;
} ncs;

ncs* ncs_create(control*);
void ncs_recalc(ncs*);

#endif
