#pragma once

#include <malloc.h>
#include "utils.h"
#include "interval.h"

typedef struct
{
  float a, b;
} Interval;

Interval* interval_create(float a, float b);
Interval* interval_copy(Interval* i);
Interval* interval_intersection(Interval* i, Interval* j);
int interval_difference(Interval* i, Interval* j, Interval*** intervals);
int interval_empty(Interval* i);
int interval_subinterval(Interval* i, Interval* j);
int interval_overlapps(Interval* i, Interval* j);
int interval_inside(Interval* i, float t);
void interval_destroy(Interval* i);
