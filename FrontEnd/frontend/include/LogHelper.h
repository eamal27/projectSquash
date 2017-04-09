// Logging Helper class
/**
 * @author Elias Amal
 * @author Caleb Phillips
 * @author Michael Stergianis
 */

#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Account.h"
#include "Ticket.h"
#include "Util.h"
#include <ctime>

using namespace std;

class LogHelper {
public:
    LogHelper(string logsFolder);

    /**
     * Helper function to delete with login event
     * Need to set username to be used with log output file
     *
     * @param string username - username of logged in User
     */
    void login(string username);

    /**
     * Load accounts log based on absolute positions of values
     * and a fixed length of each line.
     *
     * @return A vector of Account pointers
     */
    vector<Account*> loadAccountsLog();

    /**
     * Load tickets log based on absolute positions of values
     * and a fixed length of each line.
     *
     * @return a vector of Ticket pointers
     */
    vector<Ticket*> loadTicketsLog();


    /**
     * Outputs end of session logging information and creates transaction log
     *
     * @param {Account*} a pointer to the current user that is logged in
     */
    void EndOfSession(Account* currentUser);

    /**
     * Formats user type transactions of the format
     * XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC in the log files
     * 
     * @param {int} transactionType - the transaction code number
     *                                must be one of 1, 2, 6
     * @param {string} username - the username padded to width 15
     *                            note: if there are two usernames present in 
     *                            transaction details the one passed should be 
     *                            the buyer's username. In the case of addcredit
     * @param {string} userType - the user's type
     * @param {float} availableCredit - the available credit for the user
     */
    void formatUser(int transactionType,
                      string username,
                      string userType,
                      float availableCredit);

    /**
     * Formats refund type transactions of the format
     * XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC in the log files 
     * transaction type is omitted because this formatter only handles
     * transactions of type 05 - refund
     * 
     * @param {string} buyerUsername - the buyer's username
     * @param {string} sellerUsername - the seller's username
     * @param {float} refundAmount - the amount to be refunded
     */
    void formatRefund(string buyerUsername,
                        string sellerUsername,
                        float refundAmount);

    /**
     * Formats add credit type transactions
     * transactions of type 06 - addcredit
     * 
     * @param {string} username - user to credit
     * @param {float} credit - the amount to be added
     */
    void formatAddCredit(string username, float credit);

    /**
     * Formats create type transactions
     * transactions of type 01 - Create
     *
     * @param {string} username - user to create
     * @param {string} accountType - AA, SS, BS, FS
     * @param {float} credit - the amount to initialize account to
     */
    void formatCreate(string username, string accountType, float credit);

    /**
     * Formats create type transactions
     * transactions of type 02 - Delete
     *
     * @param {string} username - user to delete
     */
    void formatDelete(string username);



    /**
     * Formats buy/sell type transactions of the format
     * XX_EEEEEEEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSSSS_TTT_PPPPPP in the log files 
     * 
     * @param {int} transactionType - The transaction code number must be one of 
     *                                must be one of 3, 4
     * @param {string} eventName - The name of the event
     * @param {string} sellerUsername - the Sellers username
     * @param {int} numberTickets - the new number of tickets available for the event
     * @param {float} ticketPrice - the price per ticket
     */
    void formatPurchase(int transactionType,
                          string eventName,
                          string sellerUsername,
                          int numberTickets,
                          float ticketPrice);

private:
    string logsFolder;
    string accountsLog;
    string ticketsLog;

    string username;

    stringstream transactionBuffer;
    stringstream ticketsBuffer;
    stringstream usersBuffer;

    /**
     * Helper function to set width and load in integer values
     * such as tickets for sale and transaction codes
     *
     * @param {stringstream} ss - the stringstream to be modified
     * @param {int} transactionType - the type of transaction
     * @param {int} width - the width of the field
     */
    void formatI(stringstream &ss, int transactionType, int width);

    /**
     * Helper function to set width and load in alphabetic fields
     *
     * @param {stringstream} ss - the stringstream to be modified
     * @param {string} word - the word to pass to ss
     * @param {int} width - the width of the field
     *                      15: username
     *                      25: event name
     */
    void formatA(stringstream &ss, string word, int width);


    /**
     * Helper function to set width and pass in numeric values
     *
     * @param {stringstream} ss - the stringstream to be modified
     * @param {float} number - the amount to be formatted
     * @param {int} width - the total width of the string output including 
     *                      the decimal point and decimal values
     */
    void formatN(stringstream &ss, float number, int width);

    /**
     * Helper function for other formatters with common output.
     * Specifically transaction codes, 1, 2,  and 6
     *
     * @param {int} transType - the transaction code number
     * @param {string} username - the username padded to width 15
     * @param {string} userType - the user's type
     * @param {float} credit - transaction dependent credit

     */
    void formatCommon(int transactionCode,
                      string username,
                      string accountType,
                      float credit);
};

enum T_CODE {
    T_LOGOUT    = 0,
    T_CREATE    = 1,
    T_DELETE    = 2,
    T_SELL      = 3,
    T_BUY       = 4,
    T_REFUND    = 5,
    T_ADDCREDIT = 6
};

#endif // LOG_HELPER_H
