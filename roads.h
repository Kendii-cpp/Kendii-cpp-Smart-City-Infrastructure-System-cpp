#ifndef ROADS_H
#define ROADS_H

#include <string>
using namespace std;

struct Road {
    int id;
    string name;
    string location;
    int traffic;      // 1 = Low, 2 = Medium, 3 = High
    int condition;    // 1 = Good, 2 = Fair, 3 = Poor
};

void roadMenu();
void viewRoads();
void printRoad(const Road& r);
int getRoadCount();
int getHighTrafficCount();
Road* getRoadArray();

#endif
