#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>
using namespace std;

struct EmergencyUnit {
    int id;
    string type;       // Ambulance, Fire Station, Police Station, ...
    string location;
    bool available;
    string response;   // Standby, Dispatched, ...
};

void emergencyMenu();
int getEmergencyCount();

#endif
