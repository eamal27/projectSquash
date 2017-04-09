// Transaction helper class
/**
 * @author Elias Amal
 * @author Caleb Phillips
 * @author Michael Stergianis
 */

#ifndef TRANSACTION_HELPER_H
#define TRANSACTION_HELPER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Account.h"
#include "Ticket.h"
#include "Errors.h"
#include "Util.h"
#include <stdio.h>
#include <unistd.h>



using namespace std;

class TransactionHelper {
public:
    // collections
    Account* currentUser;

    /**
     * @constructor
     */
    TransactionHelper();

    /**
     * @param  username username to load
     * @return Account  object of given username or null if not found
     */
    Account* loadUser(string username);

    /**
     * Set accounts as loaded by LogHelper
     * @param a vector of accounts
     */
    void setAccounts(vector<Account*> accounts);

    /**
     * Checks if any user is logged in
     * @return bool to indicate whether or not a user is logged in
     */
    bool loggedIn();

    /**
     * Login given a username and setting current user account
     * @param username username to login
     * @return bool indicating success or failure
     */
    bool login(string username);

    /**
     * Logout and set current user account to null
     * @return Account pointer to current account or null if not found
     */
    void logout();

    /**
     * Get a ticket given the event name and sellerUsername
     *
     * @param {string} eventName - the name of the event
     * @param {string} sellerUsername - the seller's username
     * @return {Ticket*} - a pointer to the matching ticket, NULL otherwise
     */
    Ticket* getTicket(string eventName, string sellerUsername);

    /**
     * Get ticket
     * @param  eventName name of event selling tickets
     * @return           ticket
     */
    Ticket* getTicket(string eventName);

    /**
     * Set tickets as loaded by LogHelper
     * @param a vector of tickets
     */
    void setTickets(vector<Ticket*> tickets);

    /**
     * @param username     username for new account
     * @param accountType  type of account (AA,FS,BS,SS)
     * @param creditAmount initial amount of credit
     * @return             error code as described in Errors.h
     */
    int create(string username, string accountType, float creditAmount);

    /**
     * @param username username of account to be deleted
     * @return         error code as described in Errors.h
     */
    int deleteUser(string username);

    /**
     * @param creditAmount amount of credit to be added to current user
     * @return             error code as described in Errors.h
     */
    int addCredit(float creditAmount);

    /**
     * @param username     username to add credit to
     * @param creditAmount amount of credit to be added
     * @return             error code as described in Errors.h
     */
    int addCreditTo(string username, float creditAmount);

    /**
     * @param eventName   name of event selling tickets
     * @param ticketCount number of tickets to be purchased
     * @param username    seller's username
     * @return            error code as described in Errors.h
     */
    int buy(string eventName, int ticketCount, string username);

    /**
     * @param username    username to load
     * @param ticketPrice price of ticket
     * @param ticketCount number of tickets
     * @return            error code as described in Errors.h
     */
    int sell(string eventName, float ticketPrice, int ticketCount);

    /**
     * @param buyerUsername  username of buyer 
     * @param sellerUsername username of seller
     * @param total          amount to be refunded
     * @return               error code as described in Errors.h
     */
    int refund(string buyerUsername, string sellerUsername, float total);

private:
    // collections 
    vector<Account*> accounts;
    vector<Ticket*> tickets;
    vector<string> deletedUsers;
    float maxAllowedCredit = 999999.00;

    /**
     * Deletes a ticket from the tickets vector
     * Ticket* ticket - the ticket to delete
     */
    void deleteTicket(Ticket* ticket);

};

#endif // TRANSACTION_HELPER_H
