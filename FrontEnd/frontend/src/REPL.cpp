#include "REPL.h"
#include <stdio.h>
#include <unistd.h>

REPL::REPL(string logsFolder) {
    this->logger = new LogHelper(logsFolder);
    this->helper = new TransactionHelper();
    helper->setTickets(logger->loadTicketsLog());
    queue<string> commandBuffer;
}

void REPL::logError(string error) {
    cout << "Invalid Command: " << error << endl;
}

void REPL::generateErrors(int errorCode) {
    for (int i = 1; i <= ERR_MAX; i*=2) {
        int index = log(i) / log(2);
        // bitwise and to see if flag is set
        if ((errorCode & i) == i) {
            logError(E_ARR[index]);
        }
    }
}

string REPL::getInput() {
    string input;
    if (!commandBuffer.empty()) {
        input = commandBuffer.front();
        commandBuffer.pop();
    } else if (isatty(fileno(stdin))) {
        // terminal input
        getline(cin, input);
    } else {
        // end of program
        exit(0);
    }
    return Util::trim(input);
}

void REPL::loginSequence() {
    if (!helper->loggedIn()) {
        //Load account logs
        helper->setAccounts(logger->loadAccountsLog());

        cout << "Users file read successfully." << endl;

        //Request a username
        cout << "Enter a username:" << endl;


        string username = getInput();

        if (helper->login(username)) {
            cout << "Welcome " << helper->currentUser->getUsername() << ", begin entering commands." << endl;
            logger->login(username);
        } else {
            this->logError(ERR.USERNAME_NOT_FOUND);
        }
    } else {
        this->logError(ERR.LOGGED_IN);
    }
}

void REPL::logoutSequence() {
    if (!helper->loggedIn()) {
        this->logError(ERR.LOGIN_FIRST);
        return;
    }
    //Output log files
    logger->EndOfSession(helper->currentUser);
    cout << "Goodbye, " << helper->currentUser->getUsername() << "!" << endl;
    helper->logout();

}

void REPL::buySequence() {
    if (!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }
    if (helper->currentUser->getAccountType() == "SS") {
        this->logError(ERR.UNPRIVILEGED);
        return;
    }

    cout << "Enter event to buy tickets for:" << endl;
    string eventName = getInput();

    cout << "Enter number of tickets you are purchasing:" << endl;
    string ticketCountStr = getInput();

    int ticketCount;
    if (Util::isInteger(ticketCountStr)){
        ticketCount = stoi(ticketCountStr);
    } else {
        logError("Ticket count must be a number.");
        return;
    }

    cout << "Enter user to buy tickets from:" << endl;
    string username = getInput();

    Ticket* ticket = helper->getTicket(eventName, username);

    if (ticket == NULL) {
        this->logError(ERR.BUY_FAIL);
        return;
    }

    float ticketPrice = ticket->ticketPrice;

    int success = helper->buy(eventName, ticketCount, username);
    if (success == E_SUCCESS) {
        // write to log file
        logger->formatPurchase(T_BUY, eventName, username, ticketCount, ticketPrice);
        cout << "Tickets purchased successfully." << endl;
    } else {
        // print out all relevant error messages
        generateErrors(success);
    }
}

void REPL::sellSequence() {
    if (!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }

    cout << "Enter an event to sell tickets for:" << endl;
    string eventName = getInput();

    cout << "Enter the price per ticket:" << endl;
    string ticketPriceStr = getInput();
    float ticketPrice;
    if (Util::isFloat(ticketPriceStr)){
        ticketPrice = stof(ticketPriceStr);
    } else {
        logError("Ticket price must be a number.");
        return;
    }

    cout << "Enter the number of tickets you are selling:" << endl;
    string ticketCountStr = getInput();
    int ticketCount;
    if (Util::isInteger(ticketCountStr)){
        ticketCount = stoi(ticketCountStr);
    } else {
        logError("Ticket count must be a number.");
        return;
    }

    int success = helper->sell(eventName, ticketPrice, ticketCount);
    if (success == E_SUCCESS) {
        // write to log file
        logger->formatPurchase(T_SELL, eventName,
                                helper->currentUser->getUsername(),
                                ticketCount, ticketPrice);

        // output information to user
        cout << fixed << setprecision(2) << "Selling "
                << ticketCount << " ticket(s) for "
                << eventName << " at $"
                << ticketPrice << " each." << endl;
    } else {
        generateErrors(success);
    }
}

void REPL::deleteSequence() {
    if (!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }
    if (!helper->currentUser->isAdmin()) {
        logError(ERR.UNPRIVILEGED);
        return;
    }
    cout << "Enter a username:" << endl;
    string username = getInput();

    int success = helper->deleteUser(username);
    if (success == E_SUCCESS) {
        logger->formatDelete(username);
        cout << username << " deleted successfully." << endl;
    } else {
        generateErrors(success);
    }
}

void REPL::refundSequence() {
    if (!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }
    if (!helper->currentUser->isAdmin()) {
        logError(ERR.UNPRIVILEGED);
        return;
    }
    cout << "Enter original buyer:" << endl;
    string buyerUsername = getInput();

    cout << "Enter original seller:" << endl;
    string sellerUsername = getInput();

    cout << "Enter total amount of original purchase:" << endl;

    string totalPriceStr = getInput();
    float totalPrice;
    if (Util::isFloat(totalPriceStr)){
        totalPrice = stof(totalPriceStr);
    } else {
        logError("Total price must be a number.");
        return;
    }
    int success = helper->refund(buyerUsername, sellerUsername, totalPrice);
    if (success == E_SUCCESS) {
        // write to log file
        logger->formatRefund(buyerUsername, sellerUsername, totalPrice);

        // output information to user
        cout << fixed << setprecision(2)
                << "$" << totalPrice
                << " successfully transferred from "
                << sellerUsername << " to "
                << buyerUsername << "." << endl;
    } else {
        generateErrors(success);
    }
}

void REPL::addcreditSequence() {
    if (!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }
    bool admin = helper->currentUser->isAdmin();
    string username;
    if (admin) {
        cout << "Enter a username to add credit to:" << endl;
        username = getInput();
    } else {
        username = helper->currentUser->getUsername();
    }

    cout << "Enter amount of credit to add:" << endl;

    string creditAmountStr = getInput();
    float creditAmount;
    if (Util::isFloat(creditAmountStr)){
        creditAmount = stof(creditAmountStr);
    } else {
        logError("Credit must be numeric.");
        return;
    }
    int success;
    if (admin) {
        success = helper->addCreditTo(username, creditAmount);
    } else {
        success = helper->addCredit(creditAmount);
    }
    if (success == E_SUCCESS) {
        // write to log file
        logger->formatAddCredit(username, creditAmount);

        //Successfully added $<credit amount> to <username>'s account.
        // output information to user
        cout << fixed << setprecision(2)
                << "Successfully added $"
                << creditAmount << " to "
                << username << "'s account." << endl;
    } else {
        logError(ERR.ADD_CREDIT_FAIL);
    }
}

void REPL::createSequence() {
    if(!helper->loggedIn()) {
        logError(ERR.LOGIN_FIRST);
        return;
    }
    cout << "Enter a username:" << endl;
    string username = getInput();

    cout << "Enter an account type:" << endl;
    string accountType = getInput();

    cout << "Enter a credit amount:" << endl;
    string creditAmountStr = getInput();
    float creditAmount;
    if (Util::isFloat(creditAmountStr)){
        creditAmount = stof(creditAmountStr);
    } else {
        logError("Credit must be numeric.");
        return;
    }
    int success = helper->create(username, accountType, creditAmount);
    if (success == E_SUCCESS) {
        // write to log file
        logger->formatCreate(username, accountType, creditAmount);

        cout << username << " created successfully!" << endl;
    } else {
        generateErrors(success);
    }
}

void REPL::execute() {
    string input;
    input = this->getInput();

    if (input == "exit") {
        if (!helper->loggedIn()) {
            cout << "Goodbye!" << endl;
            exit(0);
        } else {
            cout << "Invalid Command." << endl;
        }
    } else if (input == "login") {
        this->loginSequence();
    } else if (input == "logout") {
        this->logoutSequence();
    } else if (input == "sell") {
        this->sellSequence();
    } else if (input == "buy") {
        this->buySequence();
    } else if (input == "delete") {
        this->deleteSequence();
    } else if (input == "refund") {
        this->refundSequence();
    } else if (input == "addcredit") {
        this->addcreditSequence();
    } else if (input == "create") {
        this->createSequence();
    } else {
        cout << "Invalid command." << endl;
    }
}

void REPL::run() {

    string input;
    // push user inputs to queue
    while(getline(cin, input)) {
        commandBuffer.push(input);

        // if user using terminal for input
        if (isatty(fileno(stdin))) {
            execute();
        }
    }

    // executes inputs from test files
    while(!commandBuffer.empty()) {
        execute();
    }
}
