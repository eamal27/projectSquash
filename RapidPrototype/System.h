#ifndef SYSTEM_H_
#define SYSTEM_H_

extern bool logged_in;
extern std::string initialLogin(std::string systemCmd);
extern bool verifyUsername(std::string username);
extern bool initiateTransaction(std::string user_type, std::string transactin_name);
extern std::string logout();

#endif