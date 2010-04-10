#ifndef NCS_H
#define NCS_H

#include <math.h>
#include <assert.h>
#include "control.h"

typedef struct
{
  control* c;
  float* Mx;
  float* My;
} ncs;

ncs* ncs_create(control*);
void ncs_recalc(ncs*);
float ncs_eval_x(ncs*, float);
float ncs_eval_y(ncs*, float);

#endif
