// SMART CITY INFRASTRUCTURE SYSTEM - SINGLE FILE VERSION
// Generated from the multi-file project (for online compilers).
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// ---------- structs.h ----------
#ifndef STRUCTS_H
#define STRUCTS_H

// SHARED FILE: do not change a field without telling the whole group.
// Changing a struct breaks everyone's code.

using namespace std;

const int MAX_RECORDS = 50;

struct Road {
    int id;
    string name;
    string location;
    int trafficLevel;      // 1 = Low, 2 = Medium, 3 = High
    string condition;      // e.g. Good, Fair, Poor
};

struct Facility {
    int id;
    string name;
    string type;           // School, Hospital, Park, ...
    string location;
    int capacity;
    string status;         // Open, Closed, ...
};

struct EmergencyUnit {
    int id;
    string type;           // Ambulance, Fire Station, Police, ...
    string location;
    bool available;
    string responseStatus; // Standby, Responding, ...
};

struct Utility {
    int id;
    string type;           // Water, Electricity, Waste, ...
    string area;
    string status;         // Normal, Maintenance, Outage, ...
    int usageLevel;
};

struct Request {
    int id;
    string requester;
    string category;
    string location;
    int priority;          // 1 = Low ... 3 = High
    string status;         // "Pending", "In Progress", "Resolved"
};

#endif

// ---------- validation.h ----------
#ifndef VALIDATION_H
#define VALIDATION_H

using namespace std;

int    getValidInt(const string& prompt, int minVal, int maxVal);
string getNonEmptyString(const string& prompt);
string chooseOption(const string& prompt, const string options[], int count);
bool   askYesNo(const string& prompt);
void   pauseScreen();

#endif

// ---------- roads.h ----------
#ifndef ROADS_H
#define ROADS_H


void roadMenu();
void addRoad();
void viewRoads();
void updateRoad();
void deleteRoad();
void searchRoad();
void sortRoads();

// Used by the Search & Sort Center and statistics
void  printRoadHeader();
void  printRoad(const Road& r);
int   getRoadCount();
int   getHighTrafficRoadCount();
Road* getRoadArray();

#endif

// ---------- facilities.h ----------
#ifndef FACILITIES_H
#define FACILITIES_H


void facilityMenu();
void addFacility();
void viewFacilities();
void updateFacility();
void deleteFacility();
void searchFacility();

int getFacilityCount();
int getOpenFacilityCount();

#endif

// ---------- emergency.h ----------
#ifndef EMERGENCY_H
#define EMERGENCY_H


void emergencyMenu();
void addEmergencyUnit();
void viewEmergencyUnits();
void updateEmergencyUnit();
void deleteEmergencyUnit();
void searchEmergencyUnit();

int getEmergencyUnitCount();
int getAvailableUnitCount();

#endif

// ---------- utilities.h ----------
#ifndef UTILITIES_H
#define UTILITIES_H


void utilityMenu();
void addUtility();
void viewUtilities();
void updateUtility();
void deleteUtility();
void searchUtility();

void cleanupUtilities();   // releases the dynamic array (called when the program exits)
void pointerDemo();        // shows address, dereferencing, pointer variables

int getUtilityCount();
int getUtilityOutageCount();

#endif

// ---------- requests.h ----------
#ifndef REQUESTS_H
#define REQUESTS_H


void requestMenu();
void addRequest();
void viewRequests();
void updateRequest();
void deleteRequest();
void searchRequest();
void changeRequestStatus();

int getRequestCount();
int getPendingRequestCount();
int getInProgressRequestCount();
int getResolvedRequestCount();

#endif

// ---------- algorithms.h ----------
#ifndef ALGORITHMS_H
#define ALGORITHMS_H


// Searching (return the index of the record, or -1 if not found).
// "steps" is filled with how many records were checked, so we can compare the two.
int linearSearchRoadById(const Road arr[], int n, int id, int &steps);
int binarySearchRoadById(const Road arr[], int n, int id, int &steps);   // array MUST be sorted by ID

// Sorting
void bubbleSortRoadsById(Road arr[], int n);
void selectionSortRoadsByName(Road arr[], int n);
void insertionSortRoadsByStatus(Road arr[], int n);

// Menu for the Search & Sort Center (main menu option 7)
void searchSortCenter();

#endif

// ---------- matrix.h ----------
#ifndef MATRIX_H
#define MATRIX_H

void matrixMenu();
void displayMatrix();
void countConnections();
void changeConnection();
void twoStepRoutes();
int  getTotalConnections();

#endif

// ---------- statistics.h ----------
#ifndef STATISTICS_H
#define STATISTICS_H

void showStatistics();

#endif

// ---------- validation.cpp ----------
// INPUT VALIDATION HELPERS (used by every module)
using namespace std;

// Keeps asking until the user types a whole number from minVal to maxVal.
// If the user types letters, cin goes into a "fail" state, so we clear it
// and throw away the bad input before asking again.
int getValidInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) exit(0);   // input ended (e.g. piped test), stop instead of looping forever
        cout << "Invalid input. Enter a number from " << minVal << " to " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Keeps asking until the user types something that is not empty.
string getNonEmptyString(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        if (!getline(cin, text)) exit(0);
        if (!text.empty()) return text;
        cout << "Input cannot be empty.\n";
    }
}

// Shows a numbered list of options and returns the chosen text.
// This prevents typos in fields like Status or Type.
string chooseOption(const string& prompt, const string options[], int count) {
    cout << prompt << "\n";
    for (int i = 0; i < count; i++)
        cout << "  [" << i + 1 << "] " << options[i] << "\n";
    int pick = getValidInt("  Choice: ", 1, count);
    return options[pick - 1];
}

bool askYesNo(const string& prompt) {
    string text;
    while (true) {
        cout << prompt << " (y/n): ";
        if (!getline(cin, text)) exit(0);
        if (text == "y" || text == "Y") return true;
        if (text == "n" || text == "N") return false;
        cout << "Please type y or n.\n";
    }
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

// ---------- roads.cpp ----------
// MODULE 1: ROAD & TRANSPORTATION MANAGEMENT
// Uses a fixed-size ARRAY of Road structs plus a counter (roadCount).
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

// ---------- facilities.cpp ----------
// MODULE 2: PUBLIC FACILITY MANAGEMENT (array-based, same pattern as roads.cpp)
using namespace std;

static Facility facilities[MAX_RECORDS];
static int facilityCount = 0;

static const string TYPES_fac[5] = {"School", "Hospital", "Park", "Government Office", "Evacuation Center"};
static const string STATUSES_fac[3] = {"Open", "Closed", "Under Maintenance"};

static void printHeader_fac() {
    cout << left << setw(8) << "ID" << setw(22) << "Name" << setw(20) << "Type"
         << setw(16) << "Location" << setw(10) << "Capacity" << "Status\n";
    cout << string(84, '-') << "\n";
}

static void printFacility(const Facility& f) {
    cout << left << setw(8) << f.id << setw(22) << f.name << setw(20) << f.type
         << setw(16) << f.location << setw(10) << f.capacity << f.status << "\n";
}

static int findIndex_fac(int id) {
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
    if (findIndex_fac(f.id) != -1) { cout << "A facility with that ID already exists.\n"; return; }
    f.name = getNonEmptyString("Facility name: ");
    f.type = chooseOption("Facility type:", TYPES_fac, 5);
    f.location = getNonEmptyString("Location: ");
    f.capacity = getValidInt("Capacity (1-100000): ", 1, 100000);
    f.status = chooseOption("Status:", STATUSES_fac, 3);
    facilities[facilityCount++] = f;
    cout << "Facility added successfully.\n";
}

void viewFacilities() {
    if (facilityCount == 0) { cout << "No facilities recorded.\n"; return; }
    printHeader_fac();
    for (int i = 0; i < facilityCount; i++) printFacility(facilities[i]);
}

void updateFacility() {
    if (facilityCount == 0) { cout << "No facilities to update.\n"; return; }
    int idx = findIndex_fac(getValidInt("Enter Facility ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    cout << "Current record:\n";
    printHeader_fac();
    printFacility(facilities[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    facilities[idx].name = getNonEmptyString("Facility name: ");
    facilities[idx].type = chooseOption("Facility type:", TYPES_fac, 5);
    facilities[idx].location = getNonEmptyString("Location: ");
    facilities[idx].capacity = getValidInt("Capacity (1-100000): ", 1, 100000);
    facilities[idx].status = chooseOption("Status:", STATUSES_fac, 3);
    cout << "Facility updated.\n";
}

void deleteFacility() {
    if (facilityCount == 0) { cout << "No facilities to delete.\n"; return; }
    int idx = findIndex_fac(getValidInt("Enter Facility ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    printHeader_fac();
    printFacility(facilities[idx]);
    if (!askYesNo("Delete this facility?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < facilityCount - 1; i++) facilities[i] = facilities[i + 1];
    facilityCount--;
    cout << "Facility deleted.\n";
}

void searchFacility() {
    if (facilityCount == 0) { cout << "No facilities recorded.\n"; return; }
    int idx = findIndex_fac(getValidInt("Enter Facility ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Facility not found.\n"; return; }
    printHeader_fac();
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

// ---------- emergency.cpp ----------
// MODULE 3: EMERGENCY SERVICE MANAGEMENT (array-based)
using namespace std;

static EmergencyUnit units[MAX_RECORDS];
static int unitCount = 0;

static const string TYPES_emg[4] = {"Ambulance", "Fire Station", "Police Station", "Rescue Unit"};
static const string RESPONSES_emg[3] = {"Standby", "Dispatched", "On Scene"};

static void printHeader_emg() {
    cout << left << setw(8) << "ID" << setw(18) << "Type" << setw(18) << "Location"
         << setw(12) << "Available" << "Response Status\n";
    cout << string(68, '-') << "\n";
}

static void printUnit(const EmergencyUnit& u) {
    cout << left << setw(8) << u.id << setw(18) << u.type << setw(18) << u.location
         << setw(12) << (u.available ? "Yes" : "No") << u.responseStatus << "\n";
}

static int findIndex_emg(int id) {
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
    if (findIndex_emg(u.id) != -1) { cout << "A unit with that ID already exists.\n"; return; }
    u.type = chooseOption("Unit type:", TYPES_emg, 4);
    u.location = getNonEmptyString("Location: ");
    u.available = getValidInt("Available? (1=Yes, 2=No): ", 1, 2) == 1;
    u.responseStatus = chooseOption("Response status:", RESPONSES_emg, 3);
    units[unitCount++] = u;
    cout << "Emergency unit added successfully.\n";
}

void viewEmergencyUnits() {
    if (unitCount == 0) { cout << "No emergency units recorded.\n"; return; }
    printHeader_emg();
    for (int i = 0; i < unitCount; i++) printUnit(units[i]);
}

void updateEmergencyUnit() {
    if (unitCount == 0) { cout << "No units to update.\n"; return; }
    int idx = findIndex_emg(getValidInt("Enter Unit ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    cout << "Current record:\n";
    printHeader_emg();
    printUnit(units[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    units[idx].type = chooseOption("Unit type:", TYPES_emg, 4);
    units[idx].location = getNonEmptyString("Location: ");
    units[idx].available = getValidInt("Available? (1=Yes, 2=No): ", 1, 2) == 1;
    units[idx].responseStatus = chooseOption("Response status:", RESPONSES_emg, 3);
    cout << "Emergency unit updated.\n";
}

void deleteEmergencyUnit() {
    if (unitCount == 0) { cout << "No units to delete.\n"; return; }
    int idx = findIndex_emg(getValidInt("Enter Unit ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    printHeader_emg();
    printUnit(units[idx]);
    if (!askYesNo("Delete this unit?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < unitCount - 1; i++) units[i] = units[i + 1];
    unitCount--;
    cout << "Emergency unit deleted.\n";
}

void searchEmergencyUnit() {
    if (unitCount == 0) { cout << "No emergency units recorded.\n"; return; }
    int idx = findIndex_emg(getValidInt("Enter Unit ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Unit not found.\n"; return; }
    printHeader_emg();
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

// ---------- utilities.cpp ----------
// MODULE 4: UTILITY MONITORING
// This module stores its records in a DYNAMIC array (new[] / delete[]) and
// demonstrates POINTERS. The array starts small and grows when it gets full.
using namespace std;

static Utility* utilities = nullptr;   // pointer to the first element of the dynamic array
static int utilCapacity = 0;           // how many records the array can hold right now
static int utilCount = 0;              // how many are used

static const string TYPES_utl[4] = {"Water", "Electricity", "Waste Management", "Gas"};
static const string STATUSES_utl[3] = {"Normal", "Maintenance", "Outage"};

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

static void printHeader_utl() {
    cout << left << setw(8) << "ID" << setw(20) << "Type" << setw(18) << "Area"
         << setw(14) << "Status" << "Usage\n";
    cout << string(66, '-') << "\n";
}

static void printUtility(const Utility* u) {   // takes a POINTER to one record
    cout << left << setw(8) << u->id << setw(20) << u->type << setw(18) << u->area
         << setw(14) << u->status << u->usageLevel << "%\n";
}

static int findIndex_utl(int id) {
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
    if (findIndex_utl(u.id) != -1) { cout << "A utility with that ID already exists.\n"; return; }
    u.type = chooseOption("Utility type:", TYPES_utl, 4);
    u.area = getNonEmptyString("Area: ");
    u.status = chooseOption("Status:", STATUSES_utl, 3);
    u.usageLevel = getValidInt("Usage level (0-100%): ", 0, 100);
    utilities[utilCount++] = u;
    cout << "Utility added successfully.\n";
}

void viewUtilities() {
    if (utilCount == 0) { cout << "No utility records.\n"; return; }
    printHeader_utl();
    for (int i = 0; i < utilCount; i++) printUtility(&utilities[i]);
}

void updateUtility() {
    if (utilCount == 0) { cout << "No utilities to update.\n"; return; }
    int idx = findIndex_utl(getValidInt("Enter Utility ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    Utility* u = &utilities[idx];   // pointer to the record we are editing
    cout << "Current record:\n";
    printHeader_utl();
    printUtility(u);
    cout << "Enter the new details (the ID cannot be changed):\n";
    u->type = chooseOption("Utility type:", TYPES_utl, 4);
    u->area = getNonEmptyString("Area: ");
    u->status = chooseOption("Status:", STATUSES_utl, 3);
    u->usageLevel = getValidInt("Usage level (0-100%): ", 0, 100);
    cout << "Utility updated.\n";
}

void deleteUtility() {
    if (utilCount == 0) { cout << "No utilities to delete.\n"; return; }
    int idx = findIndex_utl(getValidInt("Enter Utility ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    printHeader_utl();
    printUtility(&utilities[idx]);
    if (!askYesNo("Delete this utility?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < utilCount - 1; i++) utilities[i] = utilities[i + 1];
    utilCount--;
    cout << "Utility deleted.\n";
}

void searchUtility() {
    if (utilCount == 0) { cout << "No utility records.\n"; return; }
    int idx = findIndex_utl(getValidInt("Enter Utility ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Utility not found.\n"; return; }
    printHeader_utl();
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

// ---------- requests.cpp ----------
// MODULE 5: CITIZEN SERVICE REQUESTS (array-based)
using namespace std;

static Request requests[MAX_RECORDS];
static int requestCount = 0;

static const string CATEGORIES[5] = {"Road Repair", "Water Supply", "Electricity", "Garbage Collection", "Public Safety"};
static const string STATUSES_req[3] = {"Pending", "In Progress", "Resolved"};

static string priorityText(int p) {
    if (p == 1) return "Low";
    if (p == 2) return "Medium";
    return "High";
}

static void printHeader_req() {
    cout << left << setw(8) << "ID" << setw(18) << "Requester" << setw(22) << "Category"
         << setw(16) << "Location" << setw(10) << "Priority" << "Status\n";
    cout << string(80, '-') << "\n";
}

static void printRequest(const Request& r) {
    cout << left << setw(8) << r.id << setw(18) << r.requester << setw(22) << r.category
         << setw(16) << r.location << setw(10) << priorityText(r.priority) << r.status << "\n";
}

static int findIndex_req(int id) {
    for (int i = 0; i < requestCount; i++)
        if (requests[i].id == id) return i;
    return -1;
}

void addRequest() {
    if (requestCount >= MAX_RECORDS) {
        cout << "Request storage is full (" << MAX_RECORDS << ").\n";
        return;
    }
    Request r;
    r.id = getValidInt("Request ID: ", 1, 99999);
    if (findIndex_req(r.id) != -1) { cout << "A request with that ID already exists.\n"; return; }
    r.requester = getNonEmptyString("Citizen/Requester name: ");
    r.category = chooseOption("Category:", CATEGORIES, 5);
    r.location = getNonEmptyString("Location: ");
    r.priority = getValidInt("Priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    r.status = "Pending";   // every new request starts as Pending
    requests[requestCount++] = r;
    cout << "Request submitted (status: Pending).\n";
}

void viewRequests() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    printHeader_req();
    for (int i = 0; i < requestCount; i++) printRequest(requests[i]);
}

void updateRequest() {
    if (requestCount == 0) { cout << "No requests to update.\n"; return; }
    int idx = findIndex_req(getValidInt("Enter Request ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    cout << "Current record:\n";
    printHeader_req();
    printRequest(requests[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    requests[idx].requester = getNonEmptyString("Citizen/Requester name: ");
    requests[idx].category = chooseOption("Category:", CATEGORIES, 5);
    requests[idx].location = getNonEmptyString("Location: ");
    requests[idx].priority = getValidInt("Priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    requests[idx].status = chooseOption("Status:", STATUSES_req, 3);
    cout << "Request updated.\n";
}

void changeRequestStatus() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    int idx = findIndex_req(getValidInt("Enter Request ID: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    cout << "Current status: " << requests[idx].status << "\n";
    requests[idx].status = chooseOption("New status:", STATUSES_req, 3);
    cout << "Status updated.\n";
}

void deleteRequest() {
    if (requestCount == 0) { cout << "No requests to delete.\n"; return; }
    int idx = findIndex_req(getValidInt("Enter Request ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    printHeader_req();
    printRequest(requests[idx]);
    if (!askYesNo("Delete this request?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < requestCount - 1; i++) requests[i] = requests[i + 1];
    requestCount--;
    cout << "Request deleted.\n";
}

void searchRequest() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    int idx = findIndex_req(getValidInt("Enter Request ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    printHeader_req();
    printRequest(requests[idx]);
}

static int countStatus(const string& status) {
    int count = 0;
    for (int i = 0; i < requestCount; i++)
        if (requests[i].status == status) count++;
    return count;
}

int getRequestCount() { return requestCount; }
int getPendingRequestCount() { return countStatus("Pending"); }
int getInProgressRequestCount() { return countStatus("In Progress"); }
int getResolvedRequestCount() { return countStatus("Resolved"); }

void requestMenu() {
    int choice;
    do {
        cout << "\n===== CITIZEN SERVICE REQUESTS =====\n"
             << "[1] Submit Request\n[2] View Requests\n[3] Update Request\n"
             << "[4] Delete Request\n[5] Search Request\n[6] Change Status\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 6);
        switch (choice) {
            case 1: addRequest();          break;
            case 2: viewRequests();        break;
            case 3: updateRequest();       break;
            case 4: deleteRequest();       break;
            case 5: searchRequest();       break;
            case 6: changeRequestStatus(); break;
        }
    } while (choice != 0);
}

// ---------- search.cpp ----------
// SEARCHING + SEARCH & SORT CENTER
using namespace std;

// LINEAR SEARCH: check every record from the start until we find the ID.
// Works on unsorted data.  Time: O(n)  (best case O(1), worst case n checks)
int linearSearchRoadById(const Road arr[], int n, int id, int &steps) {
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (arr[i].id == id) return i;
    }
    return -1;
}

// BINARY SEARCH: look at the middle record, then throw away the half that cannot
// contain the ID. Repeat. REQUIRES data sorted by ID.  Time: O(log n)
int binarySearchRoadById(const Road arr[], int n, int id, int &steps) {
    steps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        steps++;
        if (arr[mid].id == id) return mid;
        if (arr[mid].id < id) low = mid + 1;    // ID is in the right half
        else high = mid - 1;                    // ID is in the left half
    }
    return -1;
}

void searchSortCenter() {
    int choice;
    do {
        cout << "\n=========================================\n"
             << "          SEARCH & SORT CENTER\n"
             << "          (works on Road records)\n"
             << "=========================================\n"
             << "[1] Linear Search\n[2] Binary Search\n[3] Sort by ID\n"
             << "[4] Sort by Name\n[5] Sort by Status (road condition)\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 5);

        Road* roads = getRoadArray();
        int n = getRoadCount();
        if (choice >= 1 && choice <= 5 && n == 0) {
            cout << "No road records yet. Add roads first (main menu option 1).\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id = getValidInt("Road ID to search: ", 1, 99999);
                int steps;
                int idx = linearSearchRoadById(roads, n, id, steps);
                if (idx == -1) cout << "Record not found (checked " << steps << " records).\n";
                else { cout << "Found after " << steps << " checks.\n"; printRoadHeader(); printRoad(roads[idx]); }
                break;
            }
            case 2: {
                bubbleSortRoadsById(roads, n);   // binary search needs sorted data
                cout << "(Records were sorted by ID first, because binary search requires it.)\n";
                int id = getValidInt("Road ID to search: ", 1, 99999);
                int steps;
                int idx = binarySearchRoadById(roads, n, id, steps);
                if (idx == -1) cout << "Record not found (checked " << steps << " records).\n";
                else { cout << "Found after " << steps << " checks.\n"; printRoadHeader(); printRoad(roads[idx]); }
                break;
            }
            case 3: bubbleSortRoadsById(roads, n);        cout << "Sorted by ID:\n";     viewRoads(); break;
            case 4: selectionSortRoadsByName(roads, n);   cout << "Sorted by name:\n";   viewRoads(); break;
            case 5: insertionSortRoadsByStatus(roads, n); cout << "Sorted by status:\n"; viewRoads(); break;
        }
    } while (choice != 0);
}

// ---------- sorting.cpp ----------
// SORTING ALGORITHMS (written by hand, no std::sort)
using namespace std;

// BUBBLE SORT: compare neighbours, swap if out of order. After each pass the
// largest remaining value "bubbles" to the end.
// Time: O(n^2) average/worst. If already sorted, the swapped flag stops it after
// one pass, so the best case is O(n).
void bubbleSortRoadsById(Road arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) {
                Road temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// SELECTION SORT: find the smallest remaining name and swap it into position i.
// Time: O(n^2) in every case (it always scans the rest of the array).
void selectionSortRoadsByName(Road arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].name < arr[minIndex].name) minIndex = j;
        }
        if (minIndex != i) {
            Road temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// INSERTION SORT: take the next record and slide it left into the sorted part.
// Time: O(n^2) worst/average, O(n) best case (already sorted).
void insertionSortRoadsByStatus(Road arr[], int n) {
    for (int i = 1; i < n; i++) {
        Road key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].condition > key.condition) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------- matrix.cpp ----------
// MATRIX: CITY ROAD CONNECTIVITY
// Rows and columns are districts. connectivity[i][j] == 1 means a road directly
// connects district i and district j. The matrix is symmetric (A-B means B-A).
using namespace std;

const int DISTRICTS = 4;
static const string names[DISTRICTS] = {"A", "B", "C", "D"};
static int connectivity[DISTRICTS][DISTRICTS] = {
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {0, 1, 1, 0}
};

static void printGrid(const int m[DISTRICTS][DISTRICTS]) {
    cout << "\n    ";
    for (int j = 0; j < DISTRICTS; j++) cout << names[j] << "  ";
    cout << "\n";
    for (int i = 0; i < DISTRICTS; i++) {
        cout << names[i] << "   ";
        for (int j = 0; j < DISTRICTS; j++) cout << m[i][j] << "  ";
        cout << "\n";
    }
}

// MATRIX DISPLAY: nested loops, O(n^2).
void displayMatrix() {
    cout << "\nCity Road Connectivity Matrix (1 = direct road, 0 = none)";
    printGrid(connectivity);
}

// ROW PROCESSING: the sum of a row = number of roads leaving that district.
void countConnections() {
    int bestDistrict = 0, bestCount = -1;
    cout << "\nRoad connections per district:\n";
    for (int i = 0; i < DISTRICTS; i++) {
        int sum = 0;
        for (int j = 0; j < DISTRICTS; j++) sum += connectivity[i][j];
        cout << "  District " << names[i] << ": " << sum << " connection(s)\n";
        if (sum > bestCount) { bestCount = sum; bestDistrict = i; }
    }
    cout << "Most connected district: " << names[bestDistrict] << " (" << bestCount << ")\n";
}

// Add or remove a road between two districts (keeps the matrix symmetric).
void changeConnection() {
    cout << "\nDistricts: 1=A, 2=B, 3=C, 4=D\n";
    int a = getValidInt("First district (1-4): ", 1, DISTRICTS) - 1;
    int b = getValidInt("Second district (1-4): ", 1, DISTRICTS) - 1;
    if (a == b) { cout << "A district cannot connect to itself.\n"; return; }
    int newValue = (connectivity[a][b] == 1) ? 0 : 1;
    connectivity[a][b] = newValue;
    connectivity[b][a] = newValue;
    cout << "Road between " << names[a] << " and " << names[b]
         << (newValue == 1 ? " added." : " removed.") << "\n";
}

// MATRIX MULTIPLICATION: M x M. Entry [i][j] = number of two-road routes from
// i to j. The diagonal entry [i][i] equals the number of roads at district i.
// Three nested loops, so the time is O(n^3).
void twoStepRoutes() {
    int result[DISTRICTS][DISTRICTS];
    for (int i = 0; i < DISTRICTS; i++) {
        for (int j = 0; j < DISTRICTS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < DISTRICTS; k++)
                result[i][j] += connectivity[i][k] * connectivity[k][j];
        }
    }
    cout << "\nNumber of 2-road routes between districts (matrix x matrix):";
    printGrid(result);
}

// Each road appears twice in the matrix (A-B and B-A), so divide by 2.
int getTotalConnections() {
    int sum = 0;
    for (int i = 0; i < DISTRICTS; i++)
        for (int j = 0; j < DISTRICTS; j++) sum += connectivity[i][j];
    return sum / 2;
}

void matrixMenu() {
    int choice;
    do {
        cout << "\n===== ROAD CONNECTIVITY MATRIX =====\n"
             << "[1] Display Matrix\n[2] Count Connections Per District\n"
             << "[3] Add/Remove a Connection\n[4] Two-Road Routes (Matrix Multiplication)\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 4);
        switch (choice) {
            case 1: displayMatrix();     break;
            case 2: countConnections();  break;
            case 3: changeConnection();  break;
            case 4: twoStepRoutes();     break;
        }
    } while (choice != 0);
}

// ---------- statistics.cpp ----------
// CITY STATISTICS: every number is produced by looping through the records.
using namespace std;

void showStatistics() {
    cout << "\n=========================================\n"
         << "            CITY STATISTICS\n"
         << "=========================================\n"
         << "Total Roads            : " << getRoadCount() << "\n"
         << "High Traffic Roads     : " << getHighTrafficRoadCount() << "\n"
         << "Road Connections       : " << getTotalConnections() << "\n"
         << "Public Facilities      : " << getFacilityCount() << "\n"
         << "Open Facilities        : " << getOpenFacilityCount() << "\n"
         << "Emergency Units        : " << getEmergencyUnitCount() << "\n"
         << "Available Units        : " << getAvailableUnitCount() << "\n"
         << "Utilities Monitored    : " << getUtilityCount() << "\n"
         << "Utilities in Outage    : " << getUtilityOutageCount() << "\n"
         << "Pending Requests       : " << getPendingRequestCount() << "\n"
         << "In Progress Requests   : " << getInProgressRequestCount() << "\n"
         << "Resolved Requests      : " << getResolvedRequestCount() << "\n"
         << "=========================================\n";
}

// ---------- main.cpp ----------
// SMART CITY INFRASTRUCTURE SYSTEM: main menu and program start
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
