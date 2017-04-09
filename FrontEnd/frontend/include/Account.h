// Account Superclass
/**
 * @author Elias Amal
 * @author Caleb Phillips
 * @author Michael Stergianis
 */

#include <iostream>
#include <string>
#include <vector>
#include "Ticket.h"

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
    // Methods
    /**
     * Set initial values
     * @constructor
		 * @param username
		 * @param creditAmount
		 * @param accountType
     */
    Account(string username, float creditAmount, string accountType);
    void addCredit(float creditAmount);
    void subtractCredit(float creditAmount);
    void buy(string eventName, int ticketCount);
    float getCreditAmount();
    string getUsername();
    string getAccountType();
    bool isAdmin();
    void deleteUser();
    bool isDeleted();
    float getCreditAdded();
    void setCreditAdded(float amount);
    float getCreditReceived();
    void setCreditReceived(float amount);


private:
    string accountType;
    float creditAmount;
    string username;
    bool deleted;
    float creditAdded;
    float creditReceived;
};

#endif
