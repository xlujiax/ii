#pragma once

#include <assert.h>
#include "curve.h"

int quad_roots(Curve* c, float** roots);
int cubic_roots(Curve* c, float** roots);
