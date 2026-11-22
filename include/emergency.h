#ifndef EMERGENCY_H
#define EMERGENCY_H

#include "structs.h"

void emergencyMenu();
void addEmergencyUnit();
void viewEmergencyUnits();
void updateEmergencyUnit();
void deleteEmergencyUnit();
void searchEmergencyUnit();

int getEmergencyUnitCount();
int getAvailableUnitCount();

#endif
