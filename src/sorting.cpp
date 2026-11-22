// SORTING ALGORITHMS (written by hand, no std::sort)
#include "algorithms.h"
using namespace std;

// BUBBLE SORT: compare neighbours, swap if out of order. After each pass the
// largest remaining value "bubbles" to the end.
// Time: O(n^2) average/worst. If already sorted, the swapped flag stops it after
// one pass, so the best case is O(n).
void bubbleSortRoadsById(Road arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                Road temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// SELECTION SORT: find the smallest remaining name and swap it into position i.
// Time: O(n^2) in every case (it always scans the rest of the array).
void selectionSortRoadsByName(Road arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].name < arr[minIndex].name) minIndex = j;
        }
        if (minIndex != i) {
            Road temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// INSERTION SORT: take the next record and slide it left into the sorted part.
// Time: O(n^2) worst/average, O(n) best case (already sorted).
void insertionSortRoadsByStatus(Road arr[], int n) {
    for (int i = 1; i < n; i++) {
        Road key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].condition > key.condition) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
