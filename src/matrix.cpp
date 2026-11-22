// MATRIX: CITY ROAD CONNECTIVITY
// Rows and columns are districts. connectivity[i][j] == 1 means a road directly
// connects district i and district j. The matrix is symmetric (A-B means B-A).
#include <iostream>
#include <string>
#include "matrix.h"
#include "validation.h"
using namespace std;

const int DISTRICTS = 4;
static const string names[DISTRICTS] = {"A", "B", "C", "D"};
static int connectivity[DISTRICTS][DISTRICTS] = {
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {0, 1, 1, 0}
};

static void printGrid(const int m[DISTRICTS][DISTRICTS]) {
    cout << "\n    ";
    for (int j = 0; j < DISTRICTS; j++) cout << names[j] << "  ";
    cout << "\n";
    for (int i = 0; i < DISTRICTS; i++) {
        cout << names[i] << "   ";
        for (int j = 0; j < DISTRICTS; j++) cout << m[i][j] << "  ";
        cout << "\n";
    }
}

// MATRIX DISPLAY: nested loops, O(n^2).
void displayMatrix() {
    cout << "\nCity Road Connectivity Matrix (1 = direct road, 0 = none)";
    printGrid(connectivity);
}

// ROW PROCESSING: the sum of a row = number of roads leaving that district.
void countConnections() {
    int bestDistrict = 0, bestCount = -1;
    cout << "\nRoad connections per district:\n";
    for (int i = 0; i < DISTRICTS; i++) {
        int sum = 0;
        for (int j = 0; j < DISTRICTS; j++) sum += connectivity[i][j];
        cout << "  District " << names[i] << ": " << sum << " connection(s)\n";
        if (sum > bestCount) { bestCount = sum; bestDistrict = i; }
    }
    cout << "Most connected district: " << names[bestDistrict] << " (" << bestCount << ")\n";
}

// Add or remove a road between two districts (keeps the matrix symmetric).
void changeConnection() {
    cout << "\nDistricts: 1=A, 2=B, 3=C, 4=D\n";
    int a = getValidInt("First district (1-4): ", 1, DISTRICTS) - 1;
    int b = getValidInt("Second district (1-4): ", 1, DISTRICTS) - 1;
    if (a == b) { cout << "A district cannot connect to itself.\n"; return; }
    int newValue = (connectivity[a][b] == 1) ? 0 : 1;
    connectivity[a][b] = newValue;
    connectivity[b][a] = newValue;
    cout << "Road between " << names[a] << " and " << names[b]
         << (newValue == 1 ? " added." : " removed.") << "\n";
}

// MATRIX MULTIPLICATION: M x M. Entry [i][j] = number of two-road routes from
// i to j. The diagonal entry [i][i] equals the number of roads at district i.
// Three nested loops, so the time is O(n^3).
void twoStepRoutes() {
    int result[DISTRICTS][DISTRICTS];
    for (int i = 0; i < DISTRICTS; i++) {
        for (int j = 0; j < DISTRICTS; j++) {
            result[i][j] = 0;
            for (int k = 0; k < DISTRICTS; k++)
                result[i][j] += connectivity[i][k] * connectivity[k][j];
        }
    }
    cout << "\nNumber of 2-road routes between districts (matrix x matrix):";
    printGrid(result);
}

// Each road appears twice in the matrix (A-B and B-A), so divide by 2.
int getTotalConnections() {
    int sum = 0;
    for (int i = 0; i < DISTRICTS; i++)
        for (int j = 0; j < DISTRICTS; j++) sum += connectivity[i][j];
    return sum / 2;
}

void matrixMenu() {
    int choice;
    do {
        cout << "\n===== ROAD CONNECTIVITY MATRIX =====\n"
             << "[1] Display Matrix\n[2] Count Connections Per District\n"
             << "[3] Add/Remove a Connection\n[4] Two-Road Routes (Matrix Multiplication)\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 4);
        switch (choice) {
            case 1: displayMatrix();     break;
            case 2: countConnections();  break;
            case 3: changeConnection();  break;
            case 4: twoStepRoutes();     break;
        }
    } while (choice != 0);
}
