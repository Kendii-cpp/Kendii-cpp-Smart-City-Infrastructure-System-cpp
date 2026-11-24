// SORTING: bubble sort, written by hand (no built-in sort)
#include "algorithms.h"
using namespace std;

// BUBBLE SORT: compare neighbouring records and swap them if they are in the
// wrong order. After each pass the largest remaining value ends up at the end.
// Time: O(n^2). If the data is already sorted, no swaps happen in the first
// pass, so the swapped flag lets it stop early (best case O(n)).
void bubbleSort(Road arr[], int n, int mode) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            bool outOfOrder = false;
            if (mode == 1 && arr[j].id > arr[j + 1].id) outOfOrder = true;
            else if (mode == 2 && arr[j].name > arr[j + 1].name) outOfOrder = true;
            else if (mode == 3 && arr[j].condition > arr[j + 1].condition) outOfOrder = true;

            if (outOfOrder) {
                Road temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
