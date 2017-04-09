#ifndef TICKET_H
#define TICKET_H

#include <string>

using namespace std;

struct Ticket {
    string eventName;
    string sellerUsername;
    int ticketCount;
    float ticketPrice;
};

#endif // TICKET_H
