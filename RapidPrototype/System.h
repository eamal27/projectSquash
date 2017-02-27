#ifndef SYSTEM_H_
#define SYSTEM_H_

std::string initialLogin(std::string systemCmd);
bool verifyUsername(std::string username);
bool initiateTransaction(std::string user_type, std::string transactin_name);
std::string logout();

#endif