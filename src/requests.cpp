// MODULE 5: Citizen Service Requests (array of structs)
#include <iostream>
#include "requests.h"
#include "common.h"
using namespace std;

static Request requests[MAX_RECORDS];
static int requestCount = 0;

static const string PRIORITY_NAMES[4] = {"", "Low", "Medium", "High"};
static const string STATUS_NAMES[4] = {"", "Pending", "In Progress", "Resolved"};

static void printRequest(const Request& r) {
    cout << r.id << " | " << r.requester << " | " << r.category << " | " << r.location
         << " | Priority: " << PRIORITY_NAMES[r.priority] << " | " << STATUS_NAMES[r.status] << "\n";
}

static int findRequest(int id) {
    for (int i = 0; i < requestCount; i++)
        if (requests[i].id == id) return i;
    return -1;
}

void addRequest() {
    if (requestCount >= MAX_RECORDS) {
        cout << "Request storage is full.\n";
        return;
    }
    Request r;
    r.id = getInt("Request ID: ", 1, 99999);
    if (findRequest(r.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }
    r.requester = getText("Citizen/Requester name: ");
    r.category = getText("Category (Road Repair, Water, Garbage...): ");
    r.location = getText("Location: ");
    r.priority = getInt("Priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    r.status = 1;   // a new request starts as Pending
    requests[requestCount] = r;
    requestCount++;
    cout << "Request added (Pending).\n";
}

void viewRequests() {
    if (requestCount == 0) {
        cout << "No requests recorded.\n";
        return;
    }
    for (int i = 0; i < requestCount; i++) printRequest(requests[i]);
}

void updateRequest() {
    int i = findRequest(getInt("Request ID to update: ", 1, 99999));
    if (i == -1) {
        cout << "Request not found.\n";
        return;
    }
    requests[i].priority = getInt("New priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    requests[i].status = getInt("New status (1=Pending, 2=In Progress, 3=Resolved): ", 1, 3);
    cout << "Request updated.\n";
}

void deleteRequest() {
    int i = findRequest(getInt("Request ID to delete: ", 1, 99999));
    if (i == -1) {
        cout << "Request not found.\n";
        return;
    }
    for (int j = i; j < requestCount - 1; j++) requests[j] = requests[j + 1];
    requestCount--;
    cout << "Request deleted.\n";
}

void searchRequest() {
    int i = findRequest(getInt("Request ID to search: ", 1, 99999));
    if (i == -1) cout << "Request not found.\n";
    else printRequest(requests[i]);
}

static int countStatus(int status) {
    int count = 0;
    for (int i = 0; i < requestCount; i++)
        if (requests[i].status == status) count++;
    return count;
}

int getPendingCount() { return countStatus(1); }
int getResolvedCount() { return countStatus(3); }

void requestMenu() {
    int choice;
    do {
        cout << "\n--- CITIZEN SERVICE REQUESTS ---\n"
             << "[1] Add\n[2] View\n[3] Update\n[4] Delete\n[5] Search\n[0] Back\n";
        choice = getInt("Enter your choice: ", 0, 5);
        if (choice == 1) addRequest();
        else if (choice == 2) viewRequests();
        else if (choice == 3) updateRequest();
        else if (choice == 4) deleteRequest();
        else if (choice == 5) searchRequest();
    } while (choice != 0);
}
