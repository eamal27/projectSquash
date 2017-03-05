#ifndef USER_H_
#define USER_H_

class User {
public:
  std::string filename; //the user accounts file
  std::string username; //the User's username for the account
  std::string user_acc_type; //is the user account type (eg. full-standard, admin, etc.)
  float acc_amount; //is the current amount in user's account

  /*public function declarations, access the user accounts file, and update
  the amount of cash in account, via a debit or a credit to the account */
  public:
    void setUsername(std::string username);
    std::string getUsername();
    void setUserType(std::string user_type);
    std::string getUserType();
    //void setUserAmount(std::string user_amount){
    //float getUserAmount();
    bool findUsername(std::string username);
    std::string findAccType(std::string username);
    float findAvailableCredit(std::string username);
    void debitAccount(float value);
    void creditAccount(float value);
};

#endif
