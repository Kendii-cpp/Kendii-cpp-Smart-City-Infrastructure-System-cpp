#ifndef UTILITIES_H
#define UTILITIES_H

#include "structs.h"

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
