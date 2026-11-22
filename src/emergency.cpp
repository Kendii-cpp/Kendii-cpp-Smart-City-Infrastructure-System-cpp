// MODULE 3: EMERGENCY SERVICE MANAGEMENT (array-based)
#include <iostream>
#include <iomanip>
#include "emergency.h"
#include "validation.h"
using namespace std;

static EmergencyUnit units[MAX_RECORDS];
static int unitCount = 0;

static const string TYPES[4] = {"Ambulance", "Fire Station", "Police Station", "Rescue Unit"};
static const string RESPONSES[3] = {"Standby", "Dispatched", "On Scene"};

static void printHeader() {
    cout << left << setw(8) << "ID" << setw(18) << "Type" << setw(18) << "Location"
         << setw(12) << "Available" << "Response Status\n";
    cout << string(68, '-') << "\n";
}

static void printUnit(const EmergencyUnit& u) {
    cout << left << setw(8) << u.id << setw(18) << u.type << setw(18) << u.location
         << setw(12) << (u.available ? "Yes" : "No") << u.responseStatus << "\n";
}

static int findIndex(int id) {
    for (int i = 0; i < unitCount; i++)
        if (units[i].id == id) return i;
    return -1;
}

void addEmergencyUnit() {
    if (unitCount >= MAX_RECORDS) {
        cout << "Emergency unit storage is full (" << MAX_RECORDS << ").\n";
        return;
    }
    EmergencyUnit u;
    u.id = getValidInt("Unit ID: ", 1, 99999);
    if (findIndex(u.id) != -1) { cout << "A unit with that ID already exists.\n"; return; }
    u.type = chooseOption("Unit type:", TYPES, 4);
    u.location = getNonEmptyString("Location: ");
    u.available = getValidInt("Available? (1=Yes, 2=No): ", 1, 2) == 1;
    u.responseStatus = chooseOption("Response status:", RESPONSES, 3);
    units[unitCount++] = u;
    cout << "Emergency unit added successfully.\n";
}

void viewEmergencyUnits() {
    if (unitCount == 0) { cout << "No emergency units recorded.\n"; return; }
    printHeader();
    for (int i = 0; i < unitCount; i++) printUnit(units[i]);
}

void updateEmergencyUnit() {
    if (unitCount == 0) { cout << "No units to update.\n"; return; }
    int idx = findIndex(getValidInt("Enter Unit ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    cout << "Current record:\n";
    printHeader();
    printUnit(units[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    units[idx].type = chooseOption("Unit type:", TYPES, 4);
    units[idx].location = getNonEmptyString("Location: ");
    units[idx].available = getValidInt("Available? (1=Yes, 2=No): ", 1, 2) == 1;
    units[idx].responseStatus = chooseOption("Response status:", RESPONSES, 3);
    cout << "Emergency unit updated.\n";
}

void deleteEmergencyUnit() {
    if (unitCount == 0) { cout << "No units to delete.\n"; return; }
    int idx = findIndex(getValidInt("Enter Unit ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    printHeader();
    printUnit(units[idx]);
    if (!askYesNo("Delete this unit?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < unitCount - 1; i++) units[i] = units[i + 1];
    unitCount--;
    cout << "Emergency unit deleted.\n";
}

void searchEmergencyUnit() {
    if (unitCount == 0) { cout << "No emergency units recorded.\n"; return; }
    int idx = findIndex(getValidInt("Enter Unit ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    printHeader();
    printUnit(units[idx]);
}

int getEmergencyUnitCount() { return unitCount; }

int getAvailableUnitCount() {
    int count = 0;
    for (int i = 0; i < unitCount; i++)
        if (units[i].available) count++;
    return count;
}

void emergencyMenu() {
    int choice;
    do {
        cout << "\n===== EMERGENCY SERVICE MANAGEMENT =====\n"
             << "[1] Add Unit\n[2] View Units\n[3] Update Unit\n"
             << "[4] Delete Unit\n[5] Search Unit\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 5);
        switch (choice) {
            case 1: addEmergencyUnit();     break;
            case 2: viewEmergencyUnits();   break;
            case 3: updateEmergencyUnit();  break;
            case 4: deleteEmergencyUnit();  break;
            case 5: searchEmergencyUnit();  break;
        }
    } while (choice != 0);
}
