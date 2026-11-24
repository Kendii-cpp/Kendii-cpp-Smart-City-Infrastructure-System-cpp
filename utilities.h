#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
using namespace std;

struct Utility {
    int id;
    string type;     // Water, Electricity, Waste, ...
    string area;
    string status;   // Normal, Maintenance, Outage, ...
    int usage;       // usage level, 0-100
};

void utilityMenu();
void cleanupUtilities();   // frees the dynamic array
void pointerDemo();        // address, dereferencing, pointer variable

#endif
