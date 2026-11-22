#ifndef ROADS_H
#define ROADS_H

#include "structs.h"

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
