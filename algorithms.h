#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "roads.h"

// Both searches return the index of the road, or -1 if it is not found.
int linearSearch(const Road arr[], int n, int id);
int binarySearch(const Road arr[], int n, int id);   // array must be sorted by ID

// mode: 1 = sort by ID, 2 = sort by name, 3 = sort by condition (status)
void bubbleSort(Road arr[], int n, int mode);

void searchSortCenter();

#endif
