#pragma once

#include "curve.h"
#include "line.h"
#include "hull.h"
#include "bezierclip.h"
#include "quadclip.h"

int curve_line_intersection(Curve* c, Line* l, float **pts);
int curve_line_intersection_quad(Curve* c, Line* l, float **pts);
Curve* curve_line_poly(Curve* c, Line* l);
void bezier_split(Curve* c, float u, Curve** left, Curve** right);

