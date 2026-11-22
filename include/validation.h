#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
using namespace std;

int    getValidInt(const string& prompt, int minVal, int maxVal);
string getNonEmptyString(const string& prompt);
string chooseOption(const string& prompt, const string options[], int count);
bool   askYesNo(const string& prompt);
void   pauseScreen();

#endif
