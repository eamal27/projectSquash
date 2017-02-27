#ifndef TRANSACTION_H_
#define TRANSACTION_H_

bool create(std::string username, std::string user_type);
bool addcreadit(std::string username, float credit_amount);
bool refund(std::string buyer_username, std::string seller_username, float credit_transfer);
bool buy(std::string eventTitle, int quantity, std::string seller_username);
bool sell(std::string eventTitle, float sale_price, int quantity);
bool deleteUser(std::string username);

#endif