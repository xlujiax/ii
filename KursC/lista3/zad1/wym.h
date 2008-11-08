#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef long long int Q;

Q int2_to_q(int u, int d);
int up(Q q);
int down(Q q);
int gcd(int m, int n);
Q normalize(Q q);
Q multiple(Q a, Q b);
Q divide(Q a, Q b);
Q plus(Q a, Q b);
Q minus(Q a, Q b);
Q read();
void write(Q q);
