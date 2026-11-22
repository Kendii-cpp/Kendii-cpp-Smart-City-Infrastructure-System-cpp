#ifndef STRUCTS_H
#define STRUCTS_H

// SHARED FILE: do not change a field without telling the whole group.
// Changing a struct breaks everyone's code.

#include <string>
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
