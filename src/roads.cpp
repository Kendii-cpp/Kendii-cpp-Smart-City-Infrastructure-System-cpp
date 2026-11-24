// MODULE 1: Road & Transportation Management (uses an array of structs)
#include <iostream>
#include "roads.h"
#include "algorithms.h"
#include "matrix.h"
#include "common.h"
using namespace std;

static Road roads[MAX_RECORDS];
static int roadCount = 0;

static const string TRAFFIC_NAMES[4] = {"", "Low", "Medium", "High"};
static const string CONDITION_NAMES[4] = {"", "Good", "Fair", "Poor"};

void printRoad(const Road& r) {
    cout << r.id << " | " << r.name << " | " << r.location << " | Traffic: "
         << TRAFFIC_NAMES[r.traffic] << " | Condition: " << CONDITION_NAMES[r.condition] << "\n";
}

// INSERTION: put the new record in the next free slot.
void addRoad() {
    if (roadCount >= MAX_RECORDS) {
        cout << "Road storage is full.\n";
        return;
    }
    Road r;
    r.id = getInt("Road ID: ", 1, 99999);
    if (linearSearch(roads, roadCount, r.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }
    r.name = getText("Road name: ");
    r.location = getText("Location: ");
    r.traffic = getInt("Traffic level (1=Low, 2=Medium, 3=High): ", 1, 3);
    r.condition = getInt("Condition (1=Good, 2=Fair, 3=Poor): ", 1, 3);
    roads[roadCount] = r;
    roadCount++;
    cout << "Road added.\n";
}

// TRAVERSAL: visit every used slot.
void viewRoads() {
    if (roadCount == 0) {
        cout << "No roads recorded.\n";
        return;
    }
    for (int i = 0; i < roadCount; i++) printRoad(roads[i]);
}

// UPDATING: find the record, then overwrite its fields.
void updateRoad() {
    int i = linearSearch(roads, roadCount, getInt("Road ID to update: ", 1, 99999));
    if (i == -1) {
        cout << "Road not found.\n";
        return;
    }
    roads[i].name = getText("New name: ");
    roads[i].location = getText("New location: ");
    roads[i].traffic = getInt("New traffic level (1-3): ", 1, 3);
    roads[i].condition = getInt("New condition (1-3): ", 1, 3);
    cout << "Road updated.\n";
}

// DELETION: shift the later records one step left, then reduce the count.
void deleteRoad() {
    int i = linearSearch(roads, roadCount, getInt("Road ID to delete: ", 1, 99999));
    if (i == -1) {
        cout << "Road not found.\n";
        return;
    }
    for (int j = i; j < roadCount - 1; j++) roads[j] = roads[j + 1];
    roadCount--;
    cout << "Road deleted.\n";
}

// SEARCHING: linear search by ID.
void searchRoad() {
    int i = linearSearch(roads, roadCount, getInt("Road ID to search: ", 1, 99999));
    if (i == -1) cout << "Road not found.\n";
    else printRoad(roads[i]);
}

void sortRoads() {
    bubbleSort(roads, roadCount, 1);   // 1 = sort by ID
    viewRoads();
}

int getRoadCount() { return roadCount; }
Road* getRoadArray() { return roads; }

int getHighTrafficCount() {
    int count = 0;
    for (int i = 0; i < roadCount; i++)
        if (roads[i].traffic == 3) count++;
    return count;
}

void roadMenu() {
    int choice;
    do {
        cout << "\n--- ROAD & TRANSPORTATION ---\n"
             << "[1] Add Road\n[2] View Roads\n[3] Update Road\n[4] Delete Road\n"
             << "[5] Search Road\n[6] Sort Roads\n[7] Road Connectivity Matrix\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 7);
        if (choice == 1) addRoad();
        else if (choice == 2) viewRoads();
        else if (choice == 3) updateRoad();
        else if (choice == 4) deleteRoad();
        else if (choice == 5) searchRoad();
        else if (choice == 6) sortRoads();
        else if (choice == 7) matrixMenu();
    } while (choice != 0);
}
