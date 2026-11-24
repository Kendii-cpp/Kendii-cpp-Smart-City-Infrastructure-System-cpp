#ifndef REQUESTS_H
#define REQUESTS_H

#include <string>
using namespace std;

struct Request {
    int id;
    string requester;
    string category;
    string location;
    int priority;     // 1 = Low, 2 = Medium, 3 = High
    int status;       // 1 = Pending, 2 = In Progress, 3 = Resolved
};

void requestMenu();
int getPendingCount();
int getResolvedCount();

#endif
