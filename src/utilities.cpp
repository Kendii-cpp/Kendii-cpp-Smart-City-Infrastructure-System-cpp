// MODULE 4: Utility Monitoring
// This module uses DYNAMIC MEMORY: the array is created with new[] and
// released with delete[]. It also shows basic POINTER use.
#include <iostream>
#include "utilities.h"
#include "common.h"
using namespace std;

static Utility* utilities = nullptr;   // pointer to the dynamic array
static int utilCapacity = 0;           // size we asked for
static int utilCount = 0;              // how many slots are used

// Called from main() when the program exits.
// delete[] is needed (not plain delete) because the memory came from new[].
// Setting the pointer to nullptr stops it from pointing at freed memory.
void cleanupUtilities() {
    delete[] utilities;
    utilities = nullptr;
    utilCapacity = 0;
    utilCount = 0;
}

static void printUtility(const Utility* u) {   // u is a pointer to one record
    cout << u->id << " | " << u->type << " | " << u->area << " | " << u->status
         << " | Usage: " << u->usage << "%\n";
}

static int findUtility(int id) {
    for (int i = 0; i < utilCount; i++)
        if (utilities[i].id == id) return i;
    return -1;
}

void addUtility() {
    if (utilCount >= utilCapacity) {
        cout << "Utility storage is full.\n";
        return;
    }
    Utility u;
    u.id = getInt("Utility ID: ", 1, 99999);
    if (findUtility(u.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }
    u.type = getText("Type (Water, Electricity, Waste...): ");
    u.area = getText("Area: ");
    u.status = getText("Status (Normal/Maintenance/Outage): ");
    u.usage = getInt("Usage level (0-100): ", 0, 100);
    utilities[utilCount] = u;
    utilCount++;
    cout << "Utility added.\n";
}

void viewUtilities() {
    if (utilCount == 0) {
        cout << "No utility records.\n";
        return;
    }
    for (int i = 0; i < utilCount; i++) printUtility(&utilities[i]);
}

void updateUtility() {
    int i = findUtility(getInt("Utility ID to update: ", 1, 99999));
    if (i == -1) {
        cout << "Utility not found.\n";
        return;
    }
    utilities[i].type = getText("New type: ");
    utilities[i].area = getText("New area: ");
    utilities[i].status = getText("New status: ");
    utilities[i].usage = getInt("New usage level (0-100): ", 0, 100);
    cout << "Utility updated.\n";
}

void deleteUtility() {
    int i = findUtility(getInt("Utility ID to delete: ", 1, 99999));
    if (i == -1) {
        cout << "Utility not found.\n";
        return;
    }
    for (int j = i; j < utilCount - 1; j++) utilities[j] = utilities[j + 1];
    utilCount--;
    cout << "Utility deleted.\n";
}

void searchUtility() {
    int i = findUtility(getInt("Utility ID to search: ", 1, 99999));
    if (i == -1) cout << "Utility not found.\n";
    else printUtility(&utilities[i]);
}

// Basic pointer demo (shown under System Information).
void pointerDemo() {
    int value = 100;
    int* ptr = &value;                 // ptr stores the ADDRESS of value
    cout << "value               = " << value << "\n";
    cout << "address (&value)    = " << &value << "\n";
    cout << "ptr (the address)   = " << ptr << "\n";
    cout << "*ptr (dereference)  = " << *ptr << "\n";
    *ptr = 200;                        // change value through the pointer
    cout << "after *ptr = 200, value = " << value << "\n";
}

void utilityMenu() {
    if (utilities == nullptr) {        // allocate the first time we enter
        utilCapacity = getInt("How many utility records do you need? (1-100): ", 1, 100);
        utilities = new Utility[utilCapacity];
        utilCount = 0;
    }
    int choice;
    do {
        cout << "\n--- UTILITY MONITORING ---\n"
             << "[1] Add\n[2] View\n[3] Update\n[4] Delete\n[5] Search\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 5);
        if (choice == 1) addUtility();
        else if (choice == 2) viewUtilities();
        else if (choice == 3) updateUtility();
        else if (choice == 4) deleteUtility();
        else if (choice == 5) searchUtility();
    } while (choice != 0);
}
