// Maciej Pacut
// Lista 4
// Zad 3
#pragma once

#include <stdio.h>

#include "gaparray.h"

void Rebalance(GapArray* ga, float e);
int BinarySearch(GapArray* ga, int element, int left, int right); // returns place to insert in bound [left, ..., right]
void InsertToSorted(GapArray* ga, int element, int debug);
int* LibrarySort(int* arr, int sz, float e, int debug);
