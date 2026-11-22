// INPUT VALIDATION HELPERS (used by every module)
#include <iostream>
#include <limits>
#include <cstdlib>
#include "validation.h"
using namespace std;

// Keeps asking until the user types a whole number from minVal to maxVal.
// If the user types letters, cin goes into a "fail" state, so we clear it
// and throw away the bad input before asking again.
int getValidInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) exit(0);   // input ended (e.g. piped test), stop instead of looping forever
        cout << "Invalid input. Enter a number from " << minVal << " to " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Keeps asking until the user types something that is not empty.
string getNonEmptyString(const string& prompt) {
    string text;
    while (true) {
        cout << prompt;
        if (!getline(cin, text)) exit(0);
        if (!text.empty()) return text;
        cout << "Input cannot be empty.\n";
    }
}

// Shows a numbered list of options and returns the chosen text.
// This prevents typos in fields like Status or Type.
string chooseOption(const string& prompt, const string options[], int count) {
    cout << prompt << "\n";
    for (int i = 0; i < count; i++)
        cout << "  [" << i + 1 << "] " << options[i] << "\n";
    int pick = getValidInt("  Choice: ", 1, count);
    return options[pick - 1];
}

bool askYesNo(const string& prompt) {
    string text;
    while (true) {
        cout << prompt << " (y/n): ";
        if (!getline(cin, text)) exit(0);
        if (text == "y" || text == "Y") return true;
        if (text == "n" || text == "N") return false;
        cout << "Please type y or n.\n";
    }
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}
