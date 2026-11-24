// MATRIX: City Road Connectivity
// Rows and columns are districts. 1 means a road directly connects the two
// districts, 0 means it does not.
#include <iostream>
#include <string>
#include "matrix.h"
#include "common.h"
using namespace std;

const int SIZE = 4;
static const string DISTRICT_NAMES[SIZE] = {"A", "B", "C", "D"};
static int roadMatrix[SIZE][SIZE] = {
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {0, 1, 1, 0}
};

// Matrix display: nested loops, O(n^2)
void displayMatrix() {
    cout << "\n   ";
    for (int j = 0; j < SIZE; j++) cout << DISTRICT_NAMES[j] << " ";
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << DISTRICT_NAMES[i] << "  ";
        for (int j = 0; j < SIZE; j++) cout << roadMatrix[i][j] << " ";
        cout << "\n";
    }
}

// Row processing: adding up one row gives the number of roads at that district.
void countConnections() {
    for (int i = 0; i < SIZE; i++) {
        int total = 0;
        for (int j = 0; j < SIZE; j++) total += roadMatrix[i][j];
        cout << "District " << DISTRICT_NAMES[i] << " has " << total << " connection(s)\n";
    }
}

void matrixMenu() {
    int choice;
    do {
        cout << "\n--- ROAD CONNECTIVITY MATRIX ---\n"
             << "[1] Display Matrix\n[2] Count Connections per District\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 2);
        if (choice == 1) displayMatrix();
        else if (choice == 2) countConnections();
    } while (choice != 0);
}
