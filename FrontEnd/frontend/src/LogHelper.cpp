#include "LogHelper.h"

LogHelper::LogHelper(string logsFolder) {
    this->logsFolder = logsFolder;
    this->accountsLog = logsFolder + "accounts.log";
    this->ticketsLog = logsFolder + "tickets.log";
}

void LogHelper::login(string username) {
    this->username = username;
}

vector<Account*> LogHelper::loadAccountsLog() {
    //TODO fix this so it handles spaces in username
    vector<Account*> accounts;

    fstream infile(this->accountsLog);

    int usernameOffset = 0;
    int usernameSize = 15;

    int typeOffset = 16;
    int typeSize = 2;

    int creditOffset = 19;
    int creditSize = 9;

    string username, accountType;
    float creditAmount;

    string line;

    while (getline(infile, line)) {
        if (line.substr(0, 4) == "END") {
            break;
        }
        username = Util::trim(line.substr(usernameOffset, usernameSize));
        accountType = Util::trim(line.substr(typeOffset, typeSize));
        creditAmount = stof(Util::trim(line.substr(creditOffset, creditSize)));
        Account* loadedAcc = new Account(username, creditAmount, accountType);
        accounts.push_back(loadedAcc);
    }

    return accounts;
}

vector<Ticket*> LogHelper::loadTicketsLog() {
    vector<Ticket*> tickets;

    int eventOffset = 0;
    int eventSize = 25;

    int usernameOffset = 26;
    int usernameSize = 15;

    int countOffset = 42;
    int countSize = 3;

    int priceOffset = 46;
    int priceSize = 6;

    fstream infile(this->ticketsLog);

    string line;

    while (getline(infile, line)) {
        if (line.substr(0, 4) == "END") {
            break;
        }

        Ticket* ticket = new Ticket();
        ticket->eventName = Util::trim(line.substr(eventOffset, eventSize));
        ticket->sellerUsername = Util::trim(line.substr(usernameOffset, usernameSize));
        ticket->ticketCount = stoi(Util::trim(line.substr(countOffset, countSize)));
        ticket->ticketPrice = stof(Util::trim(line.substr(priceOffset, priceSize)));
        tickets.push_back(ticket);
    }
    return tickets;
}

void LogHelper::EndOfSession(Account* currentUser) {
    time_t now = time(NULL);
    tm * ptm = localtime(&now);
    char buffer[32];
    strftime(buffer, 32, "%Y-%m-%d-%H:%M:%S", ptm);
		string transaction = "transactions-";
    string filename = transaction + buffer + "-" + username + ".log";
    string path = logsFolder + "transactions/" + filename;

    formatUser(T_LOGOUT,
               currentUser->getUsername(),
               currentUser->getAccountType(),
               currentUser->getCreditAmount());
    ofstream logsFile(path, ofstream::app);
    logsFile << transactionBuffer.str();
    logsFile.close();
}

void LogHelper::formatUser(int transactionType,
                             string username,
                             string userType,
                             float availableCredit) {
    stringstream ss;
    // transaction type
    formatI(ss, transactionType, 2);
    ss << " ";

    // username
    formatA(ss, username, 15);
    ss << " ";

    // user type
    formatA(ss, userType, 2); // width should not matter, but set to 2 anyways
    ss << " ";

    // available credit
    formatN(ss, availableCredit, 9);
    transactionBuffer << ss.str() << endl;
}

void LogHelper::formatAddCredit(string username, float credit) {
    this->formatCommon(T_ADDCREDIT, username, "XX", credit);
}

void LogHelper::formatCreate(string username, string accountType, float credit) {
    this->formatCommon(T_CREATE, username, accountType, credit);
}

void LogHelper::formatDelete(string username) {
    this->formatCommon(T_DELETE, username, "XX", 0);
}

void LogHelper::formatCommon(int transactionCode,
                             string username,
                             string accountType,
                             float credit) {
    stringstream ss;
    formatI(ss, transactionCode, 2);
    ss << " ";

    formatA(ss, username, 15);
    ss << " ";

    formatA(ss, accountType, 2);
    ss << " ";

    formatN(ss, credit, 9);
    transactionBuffer << ss.str() << endl;
}

void LogHelper::formatRefund(string buyerUsername,
                               string sellerUsername,
                               float refundAmount) {
    stringstream ss;
    formatI(ss, 5, 2); // refund is always of type 05
    ss << " ";

    formatA(ss, buyerUsername, 15);
    ss << " ";

    formatA(ss, sellerUsername, 15);
    ss << " ";

    formatN(ss, refundAmount, 9);
    transactionBuffer << ss.str() << endl;
}

void LogHelper::formatPurchase(int transactionType,
                                 string eventName,
                                 string sellerUsername,
                                 int numberTickets,
                                 float ticketPrice) {
    stringstream ss;
    formatI(ss, transactionType, 2);
    ss << " ";

    formatA(ss, eventName, 25);
    ss << " ";

    formatA(ss, sellerUsername, 15);
    ss << " ";

    formatI(ss, numberTickets, 3);
    ss << " ";

    formatN(ss, ticketPrice, 6);
    transactionBuffer << ss.str() << endl;
}

void LogHelper::formatI(stringstream &ss, int transactionType, int width) {
    ss.width(width);
    ss.fill('0');
    ss << right << transactionType;
}

void LogHelper::formatA(stringstream &ss, string word, int width) {
    ss.width(width);
    ss.fill(' ');
    ss << left << word;
}

void LogHelper::formatN(stringstream &ss, float number, int width) {    
    ss.width(width);
    ss.fill('0');
    ss.precision(2);
    ss << fixed << right << number;
}
