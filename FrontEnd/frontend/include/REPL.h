#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "LogHelper.h"
#include "TransactionHelper.h"
#include "Account.h"
#include "Util.h"
#include "Errors.h"
#include <queue>
#include <cmath>

using namespace std;

class REPL {
 public:
    /**
     * @constructor
     */
    REPL(string logsFolder);

    /**
     * Main Loop for program repl, handles collection of user input
     */
    void run();
    queue<string> commandBuffer;

 private:

    LogHelper* logger;
    TransactionHelper* helper;
    ERROR ERR;
    string E_ARR[19] = {
        ERR.USERNAME_NOT_FOUND,
        ERR.LOGIN_FIRST,
        ERR.DELETE_FAIL,
        ERR.UNPRIVILEGED,
        ERR.BUY_FAIL,
        ERR.EVENT_LENGTH,
        ERR.TICKET_COUNT,
        ERR.TICKET_PRICE,
        ERR.USERNAME_LENGTH,
        ERR.USERNAME_EXISTS,
        ERR.ASCII_ONLY,
        ERR.INITIAL_CREDIT_AMOUNT,
        ERR.DUPLICATE_EVENT,
        ERR.REFUND_FAIL,
        ERR.LOGGED_IN,
        ERR.ADD_CREDIT_FAIL,
        ERR.ADD_CREDIT_MIN,
        ERR.ADD_CREDIT_MAX,
        ERR.CREATE_FAIL
    };

    /**
     * Executes the next command in the command buffer
     */
    void execute();
    /**
     * Handle outputting error message, standardizes output
     * @param error Main contents of message to be displayed
     */
    void logError(string error);

    /**
     * Given a bitwise E_CODE outputs errors for each of the set flags
     *
     * @param the set of flags over which to iterate
     */
    void generateErrors(int errorCode);

    /**
     * Request user input
     * @return Trimmed string containing a single line of user input
     */
    string getInput();

    /**
     * Handle input and output for login.
     */
    void loginSequence();

    /**
     * Handle input and output for logout.
     */
    void logoutSequence();

    /**
     * Handle input and output buy transaction
     */
    void buySequence();

    /**
     * Handle input and output sell transaction
     */
    void sellSequence();

    /**
     * Handle input and output delete transaction
     */
    void deleteSequence();

    /**
     * Handle input and output on refund transaction
     */
    void refundSequence();

    /**
     * Handle input and output on addcredit transaction
     */
    void addcreditSequence();

    /**
     * Handle input and output on create transaction
     */
    void createSequence();
};


