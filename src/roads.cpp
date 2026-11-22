// MODULE 1: ROAD & TRANSPORTATION MANAGEMENT
// Uses a fixed-size ARRAY of Road structs plus a counter (roadCount).
#include <iostream>
#include <iomanip>
#include "roads.h"
#include "algorithms.h"
#include "matrix.h"
#include "validation.h"
using namespace std;

static Road roads[MAX_RECORDS];   // the array
static int roadCount = 0;         // how many slots are actually used

static const string CONDITIONS[3] = {"Good", "Fair", "Poor"};

static string trafficText(int level) {
    if (level == 1) return "Low";
    if (level == 2) return "Medium";
    return "High";
}

void printRoadHeader() {
    cout << left << setw(8) << "ID" << setw(22) << "Name" << setw(18) << "Location"
         << setw(10) << "Traffic" << "Condition\n";
    cout << string(66, '-') << "\n";
}

void printRoad(const Road& r) {
    cout << left << setw(8) << r.id << setw(22) << r.name << setw(18) << r.location
         << setw(10) << trafficText(r.trafficLevel) << r.condition << "\n";
}

static int findRoadIndex(int id) {
    int steps;
    return linearSearchRoadById(roads, roadCount, id, steps);
}

// INSERTION: add the new record at the end of the array.
void addRoad() {
    if (roadCount >= MAX_RECORDS) {
        cout << "Road storage is full (" << MAX_RECORDS << " roads). Delete a road first.\n";
        return;
    }
    Road r;
    r.id = getValidInt("Road ID: ", 1, 99999);
    if (findRoadIndex(r.id) != -1) {
        cout << "A road with ID " << r.id << " already exists.\n";
        return;
    }
    r.name = getNonEmptyString("Road name: ");
    r.location = getNonEmptyString("Location: ");
    r.trafficLevel = getValidInt("Traffic level (1=Low, 2=Medium, 3=High): ", 1, 3);
    r.condition = chooseOption("Road condition:", CONDITIONS, 3);

    roads[roadCount] = r;
    roadCount++;
    cout << "Road added successfully.\n";
}

// TRAVERSAL: visit every used slot from 0 to roadCount - 1.
void viewRoads() {
    if (roadCount == 0) {
        cout << "No roads recorded.\n";
        return;
    }
    printRoadHeader();
    for (int i = 0; i < roadCount; i++) printRoad(roads[i]);
}

// UPDATING: find the record, then overwrite its fields.
void updateRoad() {
    if (roadCount == 0) { cout << "No roads to update.\n"; return; }
    int id = getValidInt("Enter Road ID to update: ", 1, 99999);
    int idx = findRoadIndex(id);
    if (idx == -1) { cout << "Road not found.\n"; return; }

    cout << "Current record:\n";
    printRoadHeader();
    printRoad(roads[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    roads[idx].name = getNonEmptyString("Road name: ");
    roads[idx].location = getNonEmptyString("Location: ");
    roads[idx].trafficLevel = getValidInt("Traffic level (1=Low, 2=Medium, 3=High): ", 1, 3);
    roads[idx].condition = chooseOption("Road condition:", CONDITIONS, 3);
    cout << "Road updated.\n";
}

// DELETION: shift every later record one step to the left, then shrink the count.
void deleteRoad() {
    if (roadCount == 0) { cout << "No roads to delete.\n"; return; }
    int id = getValidInt("Enter Road ID to delete: ", 1, 99999);
    int idx = findRoadIndex(id);
    if (idx == -1) { cout << "Road not found.\n"; return; }

    printRoadHeader();
    printRoad(roads[idx]);
    if (!askYesNo("Delete this road?")) { cout << "Cancelled.\n"; return; }

    for (int i = idx; i < roadCount - 1; i++) roads[i] = roads[i + 1];
    roadCount--;
    cout << "Road deleted.\n";
}

// SEARCHING: uses linear search (see search.cpp).
void searchRoad() {
    if (roadCount == 0) { cout << "No roads recorded.\n"; return; }
    int id = getValidInt("Enter Road ID to search: ", 1, 99999);
    int idx = findRoadIndex(id);
    if (idx == -1) { cout << "Road not found.\n"; return; }
    printRoadHeader();
    printRoad(roads[idx]);
}

void sortRoads() {
    if (roadCount == 0) { cout << "No roads to sort.\n"; return; }
    bubbleSortRoadsById(roads, roadCount);
    cout << "Roads sorted by ID:\n";
    viewRoads();
}

int getRoadCount() { return roadCount; }
Road* getRoadArray() { return roads; }

int getHighTrafficRoadCount() {
    int count = 0;
    for (int i = 0; i < roadCount; i++)
        if (roads[i].trafficLevel == 3) count++;
    return count;
}

void roadMenu() {
    int choice;
    do {
        cout << "\n===== ROAD & TRANSPORTATION =====\n"
             << "[1] Add Road\n[2] View Roads\n[3] Update Road\n[4] Delete Road\n"
             << "[5] Search Road\n[6] Sort Roads (by ID)\n[7] Road Connectivity Matrix\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 7);
        switch (choice) {
            case 1: addRoad();    break;
            case 2: viewRoads();  break;
            case 3: updateRoad(); break;
            case 4: deleteRoad(); break;
            case 5: searchRoad(); break;
            case 6: sortRoads();  break;
            case 7: matrixMenu(); break;
        }
    } while (choice != 0);
}
