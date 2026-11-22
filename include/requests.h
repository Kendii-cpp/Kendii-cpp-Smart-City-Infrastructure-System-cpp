#ifndef REQUESTS_H
#define REQUESTS_H

#include "structs.h"

void requestMenu();
void addRequest();
void viewRequests();
void updateRequest();
void deleteRequest();
void searchRequest();
void changeRequestStatus();

int getRequestCount();
int getPendingRequestCount();
int getInProgressRequestCount();
int getResolvedRequestCount();

#endif
