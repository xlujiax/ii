#pragma once

#include "curve.h"
#include "line.h"
#include "hull.h"
#include "bezierclip.h"

void recursive_root_finding(Curve* c, float minu, float maxu, float roots[], int *num_roots);
int curve_bezclip(Curve* c, float **roots);
void bezier_split(Curve* c, float u, Curve** left, Curve** right);
