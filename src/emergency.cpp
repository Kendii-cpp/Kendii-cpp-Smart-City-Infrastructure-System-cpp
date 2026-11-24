// MODULE 3: Emergency Service Management (array of structs)
#include <iostream>
#include "emergency.h"
#include "common.h"
using namespace std;

static EmergencyUnit units[MAX_RECORDS];
static int unitCount = 0;

static void printUnit(const EmergencyUnit& u) {
    cout << u.id << " | " << u.type << " | " << u.location << " | Available: "
         << (u.available ? "Yes" : "No") << " | " << u.response << "\n";
}

static int findUnit(int id) {
    for (int i = 0; i < unitCount; i++)
        if (units[i].id == id) return i;
    return -1;
}

void addUnit() {
    if (unitCount >= MAX_RECORDS) {
        cout << "Emergency unit storage is full.\n";
        return;
    }
    EmergencyUnit u;
    u.id = getInt("Unit ID: ", 1, 99999);
    if (findUnit(u.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }
    u.type = getText("Unit type (Ambulance, Fire Station, Police...): ");
    u.location = getText("Location: ");
    u.available = (getInt("Available? (1=Yes, 2=No): ", 1, 2) == 1);
    u.response = getText("Response status (Standby/Dispatched): ");
    units[unitCount] = u;
    unitCount++;
    cout << "Unit added.\n";
}

void viewUnits() {
    if (unitCount == 0) {
        cout << "No emergency units recorded.\n";
        return;
    }
    for (int i = 0; i < unitCount; i++) printUnit(units[i]);
}

void updateUnit() {
    int i = findUnit(getInt("Unit ID to update: ", 1, 99999));
    if (i == -1) {
        cout << "Unit not found.\n";
        return;
    }
    units[i].type = getText("New type: ");
    units[i].location = getText("New location: ");
    units[i].available = (getInt("Available? (1=Yes, 2=No): ", 1, 2) == 1);
    units[i].response = getText("New response status: ");
    cout << "Unit updated.\n";
}

void deleteUnit() {
    int i = findUnit(getInt("Unit ID to delete: ", 1, 99999));
    if (i == -1) {
        cout << "Unit not found.\n";
        return;
    }
    for (int j = i; j < unitCount - 1; j++) units[j] = units[j + 1];
    unitCount--;
    cout << "Unit deleted.\n";
}

void searchUnit() {
    int i = findUnit(getInt("Unit ID to search: ", 1, 99999));
    if (i == -1) cout << "Unit not found.\n";
    else printUnit(units[i]);
}

int getEmergencyCount() { return unitCount; }

void emergencyMenu() {
    int choice;
    do {
        cout << "\n--- EMERGENCY SERVICE MANAGEMENT ---\n"
             << "[1] Add\n[2] View\n[3] Update\n[4] Delete\n[5] Search\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 5);
        if (choice == 1) addUnit();
        else if (choice == 2) viewUnits();
        else if (choice == 3) updateUnit();
        else if (choice == 4) deleteUnit();
        else if (choice == 5) searchUnit();
    } while (choice != 0);
}
