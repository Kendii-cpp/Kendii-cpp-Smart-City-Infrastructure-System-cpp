// MODULE 5: CITIZEN SERVICE REQUESTS (array-based)
#include <iostream>
#include <iomanip>
#include "requests.h"
#include "validation.h"
using namespace std;

static Request requests[MAX_RECORDS];
static int requestCount = 0;

static const string CATEGORIES[5] = {"Road Repair", "Water Supply", "Electricity", "Garbage Collection", "Public Safety"};
static const string STATUSES[3] = {"Pending", "In Progress", "Resolved"};

static string priorityText(int p) {
    if (p == 1) return "Low";
    if (p == 2) return "Medium";
    return "High";
}

static void printHeader() {
    cout << left << setw(8) << "ID" << setw(18) << "Requester" << setw(22) << "Category"
         << setw(16) << "Location" << setw(10) << "Priority" << "Status\n";
    cout << string(80, '-') << "\n";
}

static void printRequest(const Request& r) {
    cout << left << setw(8) << r.id << setw(18) << r.requester << setw(22) << r.category
         << setw(16) << r.location << setw(10) << priorityText(r.priority) << r.status << "\n";
}

static int findIndex(int id) {
    for (int i = 0; i < requestCount; i++)
        if (requests[i].id == id) return i;
    return -1;
}

void addRequest() {
    if (requestCount >= MAX_RECORDS) {
        cout << "Request storage is full (" << MAX_RECORDS << ").\n";
        return;
    }
    Request r;
    r.id = getValidInt("Request ID: ", 1, 99999);
    if (findIndex(r.id) != -1) { cout << "A request with that ID already exists.\n"; return; }
    r.requester = getNonEmptyString("Citizen/Requester name: ");
    r.category = chooseOption("Category:", CATEGORIES, 5);
    r.location = getNonEmptyString("Location: ");
    r.priority = getValidInt("Priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    r.status = "Pending";   // every new request starts as Pending
    requests[requestCount++] = r;
    cout << "Request submitted (status: Pending).\n";
}

void viewRequests() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    printHeader();
    for (int i = 0; i < requestCount; i++) printRequest(requests[i]);
}

void updateRequest() {
    if (requestCount == 0) { cout << "No requests to update.\n"; return; }
    int idx = findIndex(getValidInt("Enter Request ID to update: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    cout << "Current record:\n";
    printHeader();
    printRequest(requests[idx]);
    cout << "Enter the new details (the ID cannot be changed):\n";
    requests[idx].requester = getNonEmptyString("Citizen/Requester name: ");
    requests[idx].category = chooseOption("Category:", CATEGORIES, 5);
    requests[idx].location = getNonEmptyString("Location: ");
    requests[idx].priority = getValidInt("Priority (1=Low, 2=Medium, 3=High): ", 1, 3);
    requests[idx].status = chooseOption("Status:", STATUSES, 3);
    cout << "Request updated.\n";
}

void changeRequestStatus() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    int idx = findIndex(getValidInt("Enter Request ID: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    cout << "Current status: " << requests[idx].status << "\n";
    requests[idx].status = chooseOption("New status:", STATUSES, 3);
    cout << "Status updated.\n";
}

void deleteRequest() {
    if (requestCount == 0) { cout << "No requests to delete.\n"; return; }
    int idx = findIndex(getValidInt("Enter Request ID to delete: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    printHeader();
    printRequest(requests[idx]);
    if (!askYesNo("Delete this request?")) { cout << "Cancelled.\n"; return; }
    for (int i = idx; i < requestCount - 1; i++) requests[i] = requests[i + 1];
    requestCount--;
    cout << "Request deleted.\n";
}

void searchRequest() {
    if (requestCount == 0) { cout << "No requests recorded.\n"; return; }
    int idx = findIndex(getValidInt("Enter Request ID to search: ", 1, 99999));
    if (idx == -1) { cout << "Request not found.\n"; return; }
    printHeader();
    printRequest(requests[idx]);
}

static int countStatus(const string& status) {
    int count = 0;
    for (int i = 0; i < requestCount; i++)
        if (requests[i].status == status) count++;
    return count;
}

int getRequestCount() { return requestCount; }
int getPendingRequestCount() { return countStatus("Pending"); }
int getInProgressRequestCount() { return countStatus("In Progress"); }
int getResolvedRequestCount() { return countStatus("Resolved"); }

void requestMenu() {
    int choice;
    do {
        cout << "\n===== CITIZEN SERVICE REQUESTS =====\n"
             << "[1] Submit Request\n[2] View Requests\n[3] Update Request\n"
             << "[4] Delete Request\n[5] Search Request\n[6] Change Status\n[0] Back\n";
        choice = getValidInt("Enter your choice: ", 0, 6);
        switch (choice) {
            case 1: addRequest();          break;
            case 2: viewRequests();        break;
            case 3: updateRequest();       break;
            case 4: deleteRequest();       break;
            case 5: searchRequest();       break;
            case 6: changeRequestStatus(); break;
        }
    } while (choice != 0);
}
