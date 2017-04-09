// Account Superclass
/**
 * @author Elias Amal
 * @author Caleb Phillips
 * @author Michael Stergianis
 */

#ifndef ERROR_H
#define ERROR_H

/*
 * NOTE: Upon updating ERROR one must also update the following
 * 1) ERR_MAX located in Errors.h
 * 2) E_CODE  located in Errors.h
 * 3) E_ARR   located in REPL.h
 */

#ifndef ERR_MAX
#define ERR_MAX 262144
#endif // ERR_MAX

#include <iostream>
#include <string>

using namespace std;

struct ERROR {
    const string USERNAME_NOT_FOUND = "Invalid username.";
    const string LOGIN_FIRST = "Must login first.";
    const string DELETE_FAIL = "Failed to delete user.";
    const string UNPRIVILEGED = "Additional priveleges required for command.";
    const string BUY_FAIL = "Cannot buy tickets.";
    const string EVENT_LENGTH = "Event name must be between 1 and 25 characters.";
    const string TICKET_COUNT = "Number of tickets must be between 1 and 100.";
    const string TICKET_PRICE = "Ticket price must be greater than $0 and less than $1000.00";
    const string USERNAME_LENGTH = "Username must be between 1 and 15 characters.";
    const string USERNAME_EXISTS = "Username must be unique.";
    const string ASCII_ONLY = "Must use Ascii characters.";
    const string INITIAL_CREDIT_AMOUNT = "Initial credit amount must be a minimum of $0.00 and a maximum of $999,999.00.";
    const string DUPLICATE_EVENT = "Tickets already being sold for that event.";
    const string REFUND_FAIL = "Unable to refund credit.";
    const string LOGGED_IN = "Already logged in.";
    const string ADD_CREDIT_FAIL = "Failed to add credit.";
    const string ADD_CREDIT_MIN = "Credit amount must be greater than 0.";
    const string ADD_CREDIT_MAX = "A maximum of $1000 can be credited in a session.";
    const string CREATE_FAIL = "Failed to create user.";
};

enum E_CODE {
    E_SUCCESS                 =      0,
    E_USERNAME_NOT_FOUND      =      1,
    E_LOGIN_FIRST             =      2,
    E_DELETE_FAIL             =      4,
    E_UNPRIVILEGED            =      8,
    E_BUY_FAIL                =     16,
    E_EVENT_LENGTH            =     32,
    E_TICKET_COUNT            =     64,
    E_TICKET_PRICE            =    128,
    E_USERNAME_LENGTH         =    256,
    E_USERNAME_EXISTS         =    512,
    E_ASCII_ONLY              =   1024,
    E_INITIAL_CREDIT_AMOUNT   =   2048,
    E_DUPLICATE_EVENT         =   4096,
    E_REFUND_FAIL             =   8192,
    E_LOGGED_IN               =  16384,
    E_ADD_CREDIT_FAIL         =  32768,
    E_ADD_CREDIT_MIN          =  65536,
    E_ADD_CREDIT_MAX          = 131072,
    E_CREATE_FAIL             = 262144
};

#endif // ERROR_H
