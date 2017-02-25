

class User {

  std::string username; //the User's username for the account
  std::string user_acc_type; //is the user account type (eg. full-standard, admin, etc.)
  float acc_amount; //is the current amount in user's account

  /*public function declarations, access the user accounts file, and update
  the amount of cash in account, via a debit or a credit to the account */
  public:
    std::string findUsername(std::string user_file);
    std::string findAccType(std::string user_file);
    float findAvailableCredit(std::string user_file);
    void debitAccount(float value);
    void creditAccount(float value);
};