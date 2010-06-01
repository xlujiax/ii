#pragma once

#include "bezier.h"
#include "roots.h"
#include "interval.h"
#include "casteljau.h"

int bezier_quadclip(Bezier* b, float** roots);
int bezier_intervals(Bezier* up, Bezier* down, Interval*** intervals);
int bezier_above(Bezier* b, Interval*** intervals);

