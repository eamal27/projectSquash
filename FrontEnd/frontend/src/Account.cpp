#include "Account.h"

using namespace std;

Account::Account(string username, float creditAmount, string accountType) {
    this->username = username;
    this->creditAmount = creditAmount;
    this->accountType = accountType;
    this->deleted = false;
    this->creditAdded = 0;
    this->creditReceived = 0;
}

void Account::addCredit(float creditAmount) {
    this->creditAmount += creditAmount;
}

void Account::subtractCredit(float creditAmount) {
    this->creditAmount -= creditAmount;
}

void Account::buy(string eventName, int ticketCount) {
    // TODO: implement so that it subtracts tickets and adds credit
}

float Account::getCreditAmount() {
    return this->creditAmount;
}

string Account::getUsername() {
    return this->username;
}

string Account::getAccountType() {
    return this->accountType;
}

bool Account::isAdmin() {
    return this->accountType == "AA";
}

void Account::deleteUser() {
    this->deleted = true;
}

bool Account::isDeleted() {
    return this->deleted;
}

float Account::getCreditAdded() {
    return this->creditAdded;
}

void Account::setCreditAdded(float amount) {
    this->creditAdded = amount;
}

float Account::getCreditReceived() {
    return this->creditReceived;
}

void Account::setCreditReceived(float amount) {
    this->creditReceived = amount;
}
