#ifndef FACILITIES_H
#define FACILITIES_H

#include <string>
using namespace std;

struct Facility {
    int id;
    string name;
    string type;       // School, Hospital, Park, ...
    string location;
    int capacity;
    string status;     // Open, Closed, ...
};

void facilityMenu();
int getFacilityCount();

#endif
