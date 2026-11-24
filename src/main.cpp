// SMART CITY INFRASTRUCTURE SYSTEM: main menu
#include <iostream>
#include "roads.h"
#include "facilities.h"
#include "emergency.h"
#include "utilities.h"
#include "requests.h"
#include "algorithms.h"
#include "common.h"
using namespace std;

void showStatistics() {
    cout << "\n=========================================\n"
         << "            CITY STATISTICS\n"
         << "=========================================\n"
         << "Total Roads        : " << getRoadCount() << "\n"
         << "High Traffic Roads : " << getHighTrafficCount() << "\n"
         << "Public Facilities  : " << getFacilityCount() << "\n"
         << "Emergency Units    : " << getEmergencyCount() << "\n"
         << "Pending Requests   : " << getPendingCount() << "\n"
         << "Resolved Requests  : " << getResolvedCount() << "\n"
         << "=========================================\n";
}

void showSystemInformation() {
    cout << "\n=========================================\n"
         << "            SYSTEM INFORMATION\n"
         << "=========================================\n"
         << "Smart City Infrastructure System (C++)\n"
         << "Members: (type your group's names here)\n\n";
    pointerDemo();
}

int main() {
    int choice;
    do {
        cout << "\n=========================================\n"
             << "    SMART CITY INFRASTRUCTURE SYSTEM\n"
             << "=========================================\n"
             << "[1] Road & Transportation Management\n"
             << "[2] Public Facility Management\n"
             << "[3] Emergency Service Management\n"
             << "[4] Utility Monitoring\n"
             << "[5] Citizen Service Requests\n"
             << "[6] City Statistics\n"
             << "[7] Search and Sort Records\n"
             << "[8] System Information\n"
             << "[0] Exit\n";
        choice = getInt("Enter your choice: ", 0, 8);

        if (choice == 1) roadMenu();
        else if (choice == 2) facilityMenu();
        else if (choice == 3) emergencyMenu();
        else if (choice == 4) utilityMenu();
        else if (choice == 5) requestMenu();
        else if (choice == 6) showStatistics();
        else if (choice == 7) searchSortCenter();
        else if (choice == 8) showSystemInformation();
    } while (choice != 0);

    cleanupUtilities();   // free the dynamic array before the program ends
    cout << "Goodbye!\n";
    return 0;
}
