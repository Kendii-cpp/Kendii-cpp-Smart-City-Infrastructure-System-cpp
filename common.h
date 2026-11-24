#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_RECORDS = 50;

// Keeps asking until the user types a whole number from low to high.
// If the user types letters, cin fails, so we clear it and skip the bad input.
inline int getInt(const string& prompt, int low, int high) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= low && value <= high) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) exit(0);   // input ended, stop instead of looping forever
        cout << "Invalid input. Enter a number from " << low << " to " << high << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Keeps asking until the user types some text (not empty).
inline string getText(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        if (!getline(cin, text)) exit(0);
        if (!text.empty()) return text;
        cout << "Input cannot be empty.\n";
    }
}

#endif
