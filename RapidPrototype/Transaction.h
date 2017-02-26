#ifndef TRANSACTION_H_
#define TRANSACTION_H_

extern bool create(std::string username, std::string user_type);
extern bool addcreadit(std::string username, float credit_amount);
extern bool refund(std::string buyer_username, std::string seller_username, float credit_transfer);
extern bool buy(std::string eventTitle, int quantity, std::string seller_username);
extern bool sell(std::string eventTitle, float sale_price, int quantity);
extern bool deleteUser(std::string username);

#endif