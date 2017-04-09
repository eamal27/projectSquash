#include "TransactionHelper.h"

/*
 * note: Many of these functions return bools to indicate whether or not
 *       they have functioned correctly. This is in part so that the REPL can
 *       then print the appropriate error message.
 */

TransactionHelper::TransactionHelper() {
    this->currentUser = NULL;
}

Account* TransactionHelper::loadUser(string username) {
    for(Account* acc: this->accounts) {
        if (username == acc->getUsername()) {
            return acc;
        }
    }
    return NULL;
}

void TransactionHelper::setAccounts(vector<Account*> accounts) {
    this->accounts = accounts;
}

Ticket* TransactionHelper::getTicket(string eventName, string sellerUsername) {
    for (Ticket* ticket: this->tickets) {
        if (sellerUsername == ticket->sellerUsername && eventName == ticket->eventName) {
            return ticket;
        }
    }
    return NULL;
}

Ticket* TransactionHelper::getTicket(string eventName) {
    for(Ticket* ticket: this->tickets) {
        if (eventName == ticket->eventName) {
            return ticket;
        }
    }
    return NULL;
}

void TransactionHelper::setTickets(vector<Ticket*> tickets) {
    this->tickets = tickets;
}


bool TransactionHelper::loggedIn() {
    return this->currentUser != NULL;
}

bool TransactionHelper::login(string username) {
    bool loginSuccess = false;
    for(Account* acc: this->accounts) {
        // reset each user's creditReceived to 0
        acc->setCreditReceived(0);
        if (username == acc->getUsername()) {
            this->currentUser = acc;
            // reset current user's added credit to 0
            this->currentUser->setCreditAdded(0);
            loginSuccess = true;
        }
    }
    return loginSuccess;
}

void TransactionHelper::logout() {
    this->currentUser = NULL;
}


int TransactionHelper::create(string username, string accountType, float creditAmount) {
    int ret = E_SUCCESS;
    // if executing user is not an admin
    if (!currentUser->isAdmin()) {
        ret = ret | E_UNPRIVILEGED;
    }

    // check if using ascii characters
    for ( string::iterator it=username.begin(); it!=username.end(); ++it) {
        int c = (int) *it;
        if (c > 127 || c < 0) {
            ret = ret | E_ASCII_ONLY;
        }
    }

    // trim any trailing characters from username
    username = Util::trim(username);

    // username length
    if (username.length() > 15 || username.length() < 1) {
        ret = ret | E_USERNAME_LENGTH;
    }
    // if user already exists
    if (loadUser(username)) {
        ret = ret | E_USERNAME_EXISTS;
    }
    // check credit validity
    if (creditAmount < 0.0f || creditAmount > 999999.00) {
        ret = ret | E_INITIAL_CREDIT_AMOUNT;
    }
    return ret;
}

int TransactionHelper::deleteUser(string username) {
    int ret = E_SUCCESS;

    if (username == this->currentUser->getUsername()) {
        ret = ret | E_DELETE_FAIL;
    }

    Account* toDelete = this->loadUser(username);
    if (!toDelete) {
        ret = ret | E_USERNAME_NOT_FOUND;
    }

    if (ret == E_SUCCESS) {
        this->deletedUsers.push_back(username);
        toDelete->deleteUser();
    } else {
        ret = ret | E_DELETE_FAIL;
    }

    return ret;
}

int TransactionHelper::addCredit(float creditAmount) {
    int ret = E_SUCCESS;
    float balance = this->currentUser->getCreditAmount();
    float creditAdded = this->currentUser->getCreditAdded();
    // check if credit amount is less than 0
    if (creditAmount <= 0 ) {
        ret = ret | E_ADD_CREDIT_MIN;
    }
    // check if allowed credit amount of 1000 per session is exceeded
    if (creditAdded + creditAmount > 1000) {
        ret = ret | E_ADD_CREDIT_MAX;
    }
    // if maximum allowed credit surpassed
    if (balance + creditAmount > maxAllowedCredit) {
        ret = ret | E_ADD_CREDIT_FAIL;
    }
    if (ret == E_SUCCESS) {
        this->currentUser->addCredit(creditAmount);
        this->currentUser->setCreditAdded(creditAdded + creditAmount);
    }
    return ret;
}

int TransactionHelper::addCreditTo(string username, float creditAmount) {
    int ret = E_SUCCESS;
    if (!currentUser->isAdmin()) {
        ret = ret | E_UNPRIVILEGED;
    }
    Account* acc = this->loadUser(username);
    if (acc == NULL) {
        ret = ret | E_USERNAME_NOT_FOUND;
        return ret;
    }

    float balance = acc->getCreditAmount();
    float creditReceived = acc->getCreditReceived();
    
    // check creditAmount > 0.01
    if (creditAmount <= 0 ) {
        ret = ret | E_ADD_CREDIT_MIN;
    }
    // check total added to this account is <= 1000.00
    if (creditReceived + creditAmount > 1000) {
        ret = ret | E_ADD_CREDIT_MAX;
    }
    // check if maximum allowed credit surpassed
    if (balance + creditAmount > maxAllowedCredit) {
        ret = ret | E_ADD_CREDIT_FAIL;
    }

    if (ret == E_SUCCESS) {
        acc->addCredit(creditAmount);
        acc->setCreditReceived(creditReceived + creditAmount);
    }

    return ret;
}

void TransactionHelper::deleteTicket(Ticket* t) {
    tickets.erase(remove(tickets.begin(),
                         tickets.end(), t), tickets.end());
}

int TransactionHelper::buy(string eventName, int ticketCount, string sellerUsername) {
    // get their ticket and decrement inventory
    int ret = E_SUCCESS;
    string accType = this->currentUser->getAccountType();
    Account* seller = this->loadUser(sellerUsername);
    Ticket* ticket = this->getTicket(eventName, sellerUsername);
    float totalValue = ticketCount * ticket->ticketPrice;

    if (seller == NULL || seller->isDeleted()) {
        ret = ret | E_BUY_FAIL;
        return ret;
    }
    // check if ticket count is between 1 and 4 unless admin
    if (ticketCount < 1 || (ticketCount > 4 && accType != "AA")) {
        ret = ret | E_BUY_FAIL;
    }
    // check if event exists
    if (ticket == NULL) {
        ret = ret | E_BUY_FAIL;
        return ret;
    } else if (ticketCount > ticket->ticketCount) {
        // check if enough tickets are available for sale
        ret = ret | E_BUY_FAIL;
    } else if (this->currentUser->getCreditAmount() < totalValue) {
        // check if buyer has enough credit to buy tickets
        ret = ret | E_BUY_FAIL;
    }

    if (ret == E_SUCCESS) {
        string response;
        cout << fixed << setprecision(2) << "Confirm: Buying "
             << ticketCount << " ticket(s) at $" << ticket->ticketPrice
             << " for a total of $" << totalValue << "? (y/n)" << endl;

        if (isatty(fileno(stdin))) {
            getline(cin, response);
            response = Util::trim(response);
            while (response != "y" && response != "n") {
                cout << "Enter y or n." << endl;
                getline(cin, response);
                response = Util::trim(response);
            }
        } else {
            response = "y";
        }
        if (response == "y") {
            this->currentUser->subtractCredit(totalValue);
            ticket->ticketCount -= ticketCount;
            if (ticket->ticketCount == 0) {
                deleteTicket(ticket);
            }
        } else {
            ret = ret | E_BUY_FAIL;
        }
    }
    return ret;
}

int TransactionHelper::sell(string eventName, float ticketPrice, int ticketCount) {
    int ret = E_SUCCESS;
    string username = this->currentUser->getUsername();
    string accType = this->currentUser->getAccountType();

    if (accType == "BS") {
        ret = ret | E_UNPRIVILEGED;
    }

    if (ticketPrice > 999.99 || ticketPrice < 0.01) {
        ret = ret | E_TICKET_PRICE;
    }

    if (ticketCount > 100 || ticketCount < 1) {
        ret = ret | E_TICKET_COUNT;
    }

    if (eventName.length() > 25 || eventName.length() < 1) {
        ret = ret | E_EVENT_LENGTH;
    }


    for (const Ticket* ticket: this->tickets) {
        if ((ticket->sellerUsername == username) &&
            (ticket->eventName == eventName)) {
            ret = ret | E_DUPLICATE_EVENT;
        }
    }

    return ret;
}

int TransactionHelper::refund(string buyerUsername, string sellerUsername, float total) {
    int ret = E_SUCCESS;
    string accType = this->currentUser->getAccountType();
    if (accType != "AA") {
        ret = ret | E_UNPRIVILEGED;
    }

    Account* buyer = this->loadUser(buyerUsername);
    Account* seller = this->loadUser(sellerUsername);

    if (buyer == NULL || seller == NULL) {
        ret = ret | E_USERNAME_NOT_FOUND;
        // must return at this point so as to not access users that do not exist
        return ret;
    }

    if (!buyer || !seller) {
        ret = ret | E_USERNAME_NOT_FOUND;
        return ret;
    }

    float buyerCredit = buyer->getCreditAmount();
    float sellerCredit = seller->getCreditAmount();

    if ((sellerCredit < total) ||
        (buyerCredit + total > this->maxAllowedCredit)) {
        ret = ret | E_REFUND_FAIL;
    }

    if (ret == E_SUCCESS) {
        buyer->addCredit(total);
        seller->subtractCredit(total);
    }

    return ret;
}
