#pragma once

#include "bezier.h"
#include "roots.h"

int bezier_quadclip(Bezier* b, float** roots);
void bezier_intervals(Bezier* up, Bezier* down, float** a1, float** a2, float** a3, float** a4);
