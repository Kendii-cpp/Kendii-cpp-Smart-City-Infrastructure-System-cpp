// SEARCHING + SEARCH & SORT CENTER
#include <iostream>
#include "algorithms.h"
#include "roads.h"
#include "validation.h"
using namespace std;

// LINEAR SEARCH: check every record from the start until we find the ID.
// Works on unsorted data.  Time: O(n)  (best case O(1), worst case n checks)
int linearSearchRoadById(const Road arr[], int n, int id, int &steps) {
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (arr[i].id == id) return i;
    }
    return -1;
}

// BINARY SEARCH: look at the middle record, then throw away the half that cannot
// contain the ID. Repeat. REQUIRES data sorted by ID.  Time: O(log n)
int binarySearchRoadById(const Road arr[], int n, int id, int &steps) {
    steps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        if (arr[mid].id == id) return mid;
        if (arr[mid].id < id) low = mid + 1;    // ID is in the right half
        else high = mid - 1;                    // ID is in the left half
    }
    return -1;
}

void searchSortCenter() {
    int choice;
    do {
        cout << "\n=========================================\n"
             << "          SEARCH & SORT CENTER\n"
             << "          (works on Road records)\n"
             << "=========================================\n"
             << "[1] Linear Search\n[2] Binary Search\n[3] Sort by ID\n"
             << "[4] Sort by Name\n[5] Sort by Status (road condition)\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 5);

        Road* roads = getRoadArray();
        int n = getRoadCount();
        if (choice >= 1 && choice <= 5 && n == 0) {
            cout << "No road records yet. Add roads first (main menu option 1).\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id = getValidInt("Road ID to search: ", 1, 99999);
                int steps;
                int idx = linearSearchRoadById(roads, n, id, steps);
                if (idx == -1) cout << "Record not found (checked " << steps << " records).\n";
                else { cout << "Found after " << steps << " checks.\n"; printRoadHeader(); printRoad(roads[idx]); }
                break;
            }
            case 2: {
                bubbleSortRoadsById(roads, n);   // binary search needs sorted data
                cout << "(Records were sorted by ID first, because binary search requires it.)\n";
                int id = getValidInt("Road ID to search: ", 1, 99999);
                int steps;
                int idx = binarySearchRoadById(roads, n, id, steps);
                if (idx == -1) cout << "Record not found (checked " << steps << " records).\n";
                else { cout << "Found after " << steps << " checks.\n"; printRoadHeader(); printRoad(roads[idx]); }
                break;
            }
            case 3: bubbleSortRoadsById(roads, n);        cout << "Sorted by ID:\n";     viewRoads(); break;
            case 4: selectionSortRoadsByName(roads, n);   cout << "Sorted by name:\n";   viewRoads(); break;
            case 5: insertionSortRoadsByStatus(roads, n); cout << "Sorted by status:\n"; viewRoads(); break;
        }
    } while (choice != 0);
}
