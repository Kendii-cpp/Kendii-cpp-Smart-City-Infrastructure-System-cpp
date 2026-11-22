#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "structs.h"

// Searching (return the index of the record, or -1 if not found).
// "steps" is filled with how many records were checked, so we can compare the two.
int linearSearchRoadById(const Road arr[], int n, int id, int &steps);
int binarySearchRoadById(const Road arr[], int n, int id, int &steps);   // array MUST be sorted by ID

// Sorting
void bubbleSortRoadsById(Road arr[], int n);
void selectionSortRoadsByName(Road arr[], int n);
void insertionSortRoadsByStatus(Road arr[], int n);

// Menu for the Search & Sort Center (main menu option 7)
void searchSortCenter();

#endif
