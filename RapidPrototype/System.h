#ifndef SYSTEM_H_
#define SYSTEM_H_

bool initialLogin(std::string systemCmd);
bool verifyUsername(std::string username);
bool initiateTransaction(std::string user_type, std::string transactin_name);
bool logout();

#endif