// Maciej Pacut
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generate(int sz);
int sortedp(int* arr, int sz);
int permp(int* src, int* res, int sz);
float average_time(void (*sort)(int*, int), int sz, int times);
