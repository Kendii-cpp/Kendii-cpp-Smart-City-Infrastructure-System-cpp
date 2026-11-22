// MODULE 2: PUBLIC FACILITY MANAGEMENT (array-based, same pattern as roads.cpp)
#include <iostream>
#include <iomanip>
#include "facilities.h"
#include "validation.h"
using namespace std;

static Facility facilities[MAX_RECORDS];
static int facilityCount = 0;

static const string TYPES[5] = {"School", "Hospital", "Park", "Government Office", "Evacuation Center"};
static const string STATUSES[3] = {"Open", "Closed", "Under Maintenance"};

static void printHeader() {
    cout << left << setw(8) << "ID" << setw(22) << "Name" << setw(20) << "Type"
         << setw(16) << "Location" << setw(10) << "Capacity" << "Status\n";
    cout << string(84, '-') << "\n";
}

static void printFacility(const Facility& f) {
    cout << left << setw(8) << f.id << setw(22) << f.name << setw(20) << f.type
         << setw(16) << f.location << setw(10) << f.capacity << f.status << "\n";
}

static int findIndex(int id) {
    for (int i = 0; i < facilityCount; i++)
        if (facilities[i].id == id) return i;
    return -1;
}

void addFacility() {
    if (facilityCount >= MAX_RECORDS) {
        cout << "Facility storage is full (" << MAX_RECORDS << ").\n";
        return;
    }
    Facility f;
    f.id = getValidInt("Facility ID: ", 1, 99999);
    if (findIndex(f.id) != -1) { cout << "A facility with that ID already exists.\n"; return; }
    f.name = getNonEmptyString("Facility name: ");
    f.type = chooseOption("Facility type:", TYPES, 5);
    f.location = getNonEmptyString("Location: ");
    f.capacity = getValidInt("Capacity (1-100000): ", 1, 100000);
    f.status = chooseOption("Status:", STATUSES, 3);
    facilities[facilityCount++] = f;
    cout << "Facility added successfully.\n";
}

void viewFacilities() {
    if (facilityCount == 0) { cout << "No facilities recorded.\n"; return; }
    printHeader();
    for (int i = 0; i < facilityCount; i++) printFacility(facilities[i]);
}

void updateFacility() {
    if (facilityCount == 0) { cout << "No facilities to update.\n"; return; }
    int idx = findIndex(getValidInt("Enter Facility ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    cout << "Current record:\n";
    printHeader();
    printFacility(facilities[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    facilities[idx].name = getNonEmptyString("Facility name: ");
    facilities[idx].type = chooseOption("Facility type:", TYPES, 5);
    facilities[idx].location = getNonEmptyString("Location: ");
    facilities[idx].capacity = getValidInt("Capacity (1-100000): ", 1, 100000);
    facilities[idx].status = chooseOption("Status:", STATUSES, 3);
    cout << "Facility updated.\n";
}

void deleteFacility() {
    if (facilityCount == 0) { cout << "No facilities to delete.\n"; return; }
    int idx = findIndex(getValidInt("Enter Facility ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    printHeader();
    printFacility(facilities[idx]);
    if (!askYesNo("Delete this facility?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < facilityCount - 1; i++) facilities[i] = facilities[i + 1];
    facilityCount--;
    cout << "Facility deleted.\n";
}

void searchFacility() {
    if (facilityCount == 0) { cout << "No facilities recorded.\n"; return; }
    int idx = findIndex(getValidInt("Enter Facility ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    printHeader();
    printFacility(facilities[idx]);
}

int getFacilityCount() { return facilityCount; }

int getOpenFacilityCount() {
    int count = 0;
    for (int i = 0; i < facilityCount; i++)
        if (facilities[i].status == "Open") count++;
    return count;
}

void facilityMenu() {
    int choice;
    do {
        cout << "\n===== PUBLIC FACILITY MANAGEMENT =====\n"
             << "[1] Add Facility\n[2] View Facilities\n[3] Update Facility\n"
             << "[4] Delete Facility\n[5] Search Facility\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 5);
        switch (choice) {
            case 1: addFacility();     break;
            case 2: viewFacilities();  break;
            case 3: updateFacility();  break;
            case 4: deleteFacility();  break;
            case 5: searchFacility();  break;
        }
    } while (choice != 0);
}
