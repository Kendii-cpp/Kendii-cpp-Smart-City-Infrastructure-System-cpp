// SEARCHING + SEARCH & SORT CENTER (works on the road records)
#include <iostream>
#include "algorithms.h"
#include "roads.h"
#include "common.h"
using namespace std;

// LINEAR SEARCH: check each record one by one from the start.
// Works on unsorted data. Time: O(n)
int linearSearch(const Road arr[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

// BINARY SEARCH: look at the middle record and discard the half that cannot
// contain the ID. Repeat. The data MUST be sorted by ID. Time: O(log n)
int binarySearch(const Road arr[], int n, int id) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].id == id) return mid;
        else if (arr[mid].id < id) low = mid + 1;   // ID is in the right half
        else high = mid - 1;                        // ID is in the left half
    }
    return -1;
}

void searchSortCenter() {
    int choice;
    do {
        cout << "\n=========================================\n"
             << "          SEARCH & SORT CENTER\n"
             << "=========================================\n"
             << "[1] Linear Search\n[2] Binary Search\n[3] Sort by ID\n"
             << "[4] Sort by Name\n[5] Sort by Status\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 5);

        Road* roads = getRoadArray();
        int n = getRoadCount();
        if (choice != 0 && n == 0) {
            cout << "No road records yet. Add roads first.\n";
        } else if (choice == 1) {
            int i = linearSearch(roads, n, getInt("Road ID to search: ", 1, 99999));
            if (i == -1) cout << "Road not found.\n";
            else printRoad(roads[i]);
        } else if (choice == 2) {
            bubbleSort(roads, n, 1);   // binary search needs sorted data
            cout << "(Roads were sorted by ID first.)\n";
            int i = binarySearch(roads, n, getInt("Road ID to search: ", 1, 99999));
            if (i == -1) cout << "Road not found.\n";
            else printRoad(roads[i]);
        } else if (choice >= 3 && choice <= 5) {
            bubbleSort(roads, n, choice - 2);   // 3 -> mode 1, 4 -> mode 2, 5 -> mode 3
            viewRoads();
        }
    } while (choice != 0);
}
