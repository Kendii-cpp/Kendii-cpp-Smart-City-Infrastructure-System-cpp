// MODULE 4: UTILITY MONITORING
// This module stores its records in a DYNAMIC array (new[] / delete[]) and
// demonstrates POINTERS. The array starts small and grows when it gets full.
#include <iostream>
#include <iomanip>
#include "utilities.h"
#include "validation.h"
using namespace std;

static Utility* utilities = nullptr;   // pointer to the first element of the dynamic array
static int utilCapacity = 0;           // how many records the array can hold right now
static int utilCount = 0;              // how many are used

static const string TYPES[4] = {"Water", "Electricity", "Waste Management", "Gas"};
static const string STATUSES[3] = {"Normal", "Maintenance", "Outage"};

// Allocates the array on the HEAP with new[].
static void initUtilities() {
    utilCapacity = 5;
    utilities = new Utility[utilCapacity];
    utilCount = 0;
}

// Releases the memory. We use delete[] (not delete) because the memory was
// allocated with new[]. Plain delete would only clean up ONE element and cause
// undefined behaviour. We set the pointer to nullptr so it can never be used
// again by accident (a "dangling pointer").
void cleanupUtilities() {
    delete[] utilities;
    utilities = nullptr;
    utilCapacity = 0;
    utilCount = 0;
}

// When the array is full: allocate a bigger one, copy everything over,
// free the old one, and point to the new one.
static void growUtilities() {
    int newCapacity = utilCapacity * 2;
    Utility* bigger = new Utility[newCapacity];
    for (int i = 0; i < utilCount; i++) bigger[i] = utilities[i];
    delete[] utilities;
    utilities = bigger;
    cout << "(Storage was full: grew from " << utilCapacity << " to " << newCapacity << " records.)\n";
    utilCapacity = newCapacity;
}

static void printHeader() {
    cout << left << setw(8) << "ID" << setw(20) << "Type" << setw(18) << "Area"
         << setw(14) << "Status" << "Usage\n";
    cout << string(66, '-') << "\n";
}

static void printUtility(const Utility* u) {   // takes a POINTER to one record
    cout << left << setw(8) << u->id << setw(20) << u->type << setw(18) << u->area
         << setw(14) << u->status << u->usageLevel << "%\n";
}

static int findIndex(int id) {
    for (int i = 0; i < utilCount; i++)
        if ((utilities + i)->id == id) return i;   // pointer arithmetic
    return -1;
}

void addUtility() {
    if (utilities == nullptr) initUtilities();
    if (utilCount >= MAX_RECORDS * 4) { cout << "Utility limit reached.\n"; return; }
    if (utilCount >= utilCapacity) growUtilities();

    Utility u;
    u.id = getValidInt("Utility ID: ", 1, 99999);
    if (findIndex(u.id) != -1) { cout << "A utility with that ID already exists.\n"; return; }
    u.type = chooseOption("Utility type:", TYPES, 4);
    u.area = getNonEmptyString("Area: ");
    u.status = chooseOption("Status:", STATUSES, 3);
    u.usageLevel = getValidInt("Usage level (0-100%): ", 0, 100);
    utilities[utilCount++] = u;
    cout << "Utility added successfully.\n";
}

void viewUtilities() {
    if (utilCount == 0) { cout << "No utility records.\n"; return; }
    printHeader();
    for (int i = 0; i < utilCount; i++) printUtility(&utilities[i]);
}

void updateUtility() {
    if (utilCount == 0) { cout << "No utilities to update.\n"; return; }
    int idx = findIndex(getValidInt("Enter Utility ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    Utility* u = &utilities[idx];   // pointer to the record we are editing
    cout << "Current record:\n";
    printHeader();
    printUtility(u);
    cout << "Enter the new details (the ID cannot be changed):\n";
    u->type = chooseOption("Utility type:", TYPES, 4);
    u->area = getNonEmptyString("Area: ");
    u->status = chooseOption("Status:", STATUSES, 3);
    u->usageLevel = getValidInt("Usage level (0-100%): ", 0, 100);
    cout << "Utility updated.\n";
}

void deleteUtility() {
    if (utilCount == 0) { cout << "No utilities to delete.\n"; return; }
    int idx = findIndex(getValidInt("Enter Utility ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    printHeader();
    printUtility(&utilities[idx]);
    if (!askYesNo("Delete this utility?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < utilCount - 1; i++) utilities[i] = utilities[i + 1];
    utilCount--;
    cout << "Utility deleted.\n";
}

void searchUtility() {
    if (utilCount == 0) { cout << "No utility records.\n"; return; }
    int idx = findIndex(getValidInt("Enter Utility ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    printHeader();
    printUtility(&utilities[idx]);
}

int getUtilityCount() { return utilCount; }

int getUtilityOutageCount() {
    int count = 0;
    for (int i = 0; i < utilCount; i++)
        if (utilities[i].status == "Outage") count++;
    return count;
}

// Basic pointer demo (shown under System Information).
void pointerDemo() {
    int value = 100;
    int* ptr = &value;                  // ptr stores the ADDRESS of value
    cout << "--- Pointer demonstration ---\n";
    cout << "value                    = " << value << "\n";
    cout << "address of value (&value)= " << &value << "\n";
    cout << "ptr (holds that address) = " << ptr << "\n";
    cout << "*ptr (dereferencing)     = " << *ptr << "\n";
    *ptr = 200;                         // changing the value THROUGH the pointer
    cout << "after *ptr = 200, value = " << value << "\n";
    cout << "Utility records currently stored in dynamic memory: " << utilCount
         << " (capacity " << utilCapacity << ")\n";
}

void utilityMenu() {
    int choice;
    do {
        cout << "\n===== UTILITY MONITORING =====\n"
             << "[1] Add Utility\n[2] View Utilities\n[3] Update Utility\n"
             << "[4] Delete Utility\n[5] Search Utility\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 5);
        switch (choice) {
            case 1: addUtility();     break;
            case 2: viewUtilities();  break;
            case 3: updateUtility();  break;
            case 4: deleteUtility();  break;
            case 5: searchUtility();  break;
        }
    } while (choice != 0);
}
