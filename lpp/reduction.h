#pragma once

#include "curve.h"

Curve* curve_degree_reduction(Curve* c, int reduced_degree);
Curve* curve_degree_reduction_rec(Curve* c, int reduced_degree);
