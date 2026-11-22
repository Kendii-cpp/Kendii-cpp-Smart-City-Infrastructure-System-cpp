// CITY STATISTICS: every number is produced by looping through the records.
#include <iostream>
#include "statistics.h"
#include "roads.h"
#include "facilities.h"
#include "emergency.h"
#include "utilities.h"
#include "requests.h"
#include "matrix.h"
using namespace std;

void showStatistics() {
    cout << "\n=========================================\n"
         << "            CITY STATISTICS\n"
         << "=========================================\n"
         << "Total Roads            : " << getRoadCount() << "\n"
         << "High Traffic Roads     : " << getHighTrafficRoadCount() << "\n"
         << "Road Connections       : " << getTotalConnections() << "\n"
         << "Public Facilities      : " << getFacilityCount() << "\n"
         << "Open Facilities        : " << getOpenFacilityCount() << "\n"
         << "Emergency Units        : " << getEmergencyUnitCount() << "\n"
         << "Available Units        : " << getAvailableUnitCount() << "\n"
         << "Utilities Monitored    : " << getUtilityCount() << "\n"
         << "Utilities in Outage    : " << getUtilityOutageCount() << "\n"
         << "Pending Requests       : " << getPendingRequestCount() << "\n"
         << "In Progress Requests   : " << getInProgressRequestCount() << "\n"
         << "Resolved Requests      : " << getResolvedRequestCount() << "\n"
         << "=========================================\n";
}
