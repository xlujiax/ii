#pragma once

#include "bezier.h"

float bezier_de_casteljau(Bezier* b, float u);
void bezier_split(Bezier* b, float u, Bezier** left, Bezier** right);

