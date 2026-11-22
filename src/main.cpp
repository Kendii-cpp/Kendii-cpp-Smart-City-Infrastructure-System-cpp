// SMART CITY INFRASTRUCTURE SYSTEM: main menu and program start
#include <iostream>
#include "roads.h"
#include "facilities.h"
#include "emergency.h"
#include "utilities.h"
#include "requests.h"
#include "statistics.h"
#include "algorithms.h"
#include "validation.h"
using namespace std;

void showSystemInformation() {
    cout << "\n=========================================\n"
         << "            SYSTEM INFORMATION\n"
         << "=========================================\n"
         << "Project : Smart City Infrastructure System\n"
         << "Language: C++\n"
         << "Members : (TODO: type your group's names here)\n\n"
         << "Data structures used:\n"
         << "  - Arrays of structs (roads, facilities, emergency units, requests)\n"
         << "  - Dynamic array with new[]/delete[] (utilities)\n"
         << "  - 2D array / matrix (road connectivity)\n"
         << "  - Pointers (utilities module and the demo below)\n\n";
    pointerDemo();
}

void showMainMenu() {
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
}

int main() {
    int choice;
    do {
        showMainMenu();
        choice = getValidInt("Enter your choice: ", 0, 8);
        switch (choice) {
            case 1: roadMenu();              break;
            case 2: facilityMenu();          break;
            case 3: emergencyMenu();         break;
            case 4: utilityMenu();           break;
            case 5: requestMenu();           break;
            case 6: showStatistics();        break;
            case 7: searchSortCenter();      break;
            case 8: showSystemInformation(); break;
            case 0: cout << "Thank you for using the Smart City Infrastructure System.\n"; break;
        }
    } while (choice != 0);

    cleanupUtilities();   // free the dynamic array before exiting
    return 0;
}
