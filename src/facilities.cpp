// MODULE 2: Public Facility Management (array of structs, same pattern as roads)
#include <iostream>
#include "facilities.h"
#include "common.h"
using namespace std;

static Facility facilities[MAX_RECORDS];
static int facilityCount = 0;

static void printFacility(const Facility& f) {
    cout << f.id << " | " << f.name << " | " << f.type << " | " << f.location
         << " | Capacity: " << f.capacity << " | " << f.status << "\n";
}

static int findFacility(int id) {
    for (int i = 0; i < facilityCount; i++)
        if (facilities[i].id == id) return i;
    return -1;
}

void addFacility() {
    if (facilityCount >= MAX_RECORDS) {
        cout << "Facility storage is full.\n";
        return;
    }
    Facility f;
    f.id = getInt("Facility ID: ", 1, 99999);
    if (findFacility(f.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }
    f.name = getText("Facility name: ");
    f.type = getText("Type (School, Hospital, Park...): ");
    f.location = getText("Location: ");
    f.capacity = getInt("Capacity: ", 1, 100000);
    f.status = getText("Status (Open/Closed): ");
    facilities[facilityCount] = f;
    facilityCount++;
    cout << "Facility added.\n";
}

void viewFacilities() {
    if (facilityCount == 0) {
        cout << "No facilities recorded.\n";
        return;
    }
    for (int i = 0; i < facilityCount; i++) printFacility(facilities[i]);
}

void updateFacility() {
    int i = findFacility(getInt("Facility ID to update: ", 1, 99999));
    if (i == -1) {
        cout << "Facility not found.\n";
        return;
    }
    facilities[i].name = getText("New name: ");
    facilities[i].type = getText("New type: ");
    facilities[i].location = getText("New location: ");
    facilities[i].capacity = getInt("New capacity: ", 1, 100000);
    facilities[i].status = getText("New status: ");
    cout << "Facility updated.\n";
}

void deleteFacility() {
    int i = findFacility(getInt("Facility ID to delete: ", 1, 99999));
    if (i == -1) {
        cout << "Facility not found.\n";
        return;
    }
    for (int j = i; j < facilityCount - 1; j++) facilities[j] = facilities[j + 1];
    facilityCount--;
    cout << "Facility deleted.\n";
}

void searchFacility() {
    int i = findFacility(getInt("Facility ID to search: ", 1, 99999));
    if (i == -1) cout << "Facility not found.\n";
    else printFacility(facilities[i]);
}

int getFacilityCount() { return facilityCount; }

void facilityMenu() {
    int choice;
    do {
        cout << "\n--- PUBLIC FACILITY MANAGEMENT ---\n"
             << "[1] Add\n[2] View\n[3] Update\n[4] Delete\n[5] Search\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 5);
        if (choice == 1) addFacility();
        else if (choice == 2) viewFacilities();
        else if (choice == 3) updateFacility();
        else if (choice == 4) deleteFacility();
        else if (choice == 5) searchFacility();
    } while (choice != 0);
}
