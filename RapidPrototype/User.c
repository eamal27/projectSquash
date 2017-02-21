
/*
User
This class includes all fields and methods necessary for a user
who would be logging in and making transactions through the ticket
selling service system.
Attributes:
  username | the User's username for the account
  user_acc_type | is the user account type (eg. full-standard, admin, )
Methods:
*/

#include <iostream>
using namespace std;

class User {

  string username; //the User's username for the account
  string user_acc_type; //is the user account type (eg. full-standard, admin, etc.)
  float acc_amount; //is the current amount in user's account

  /*public function declarations, access the user accounts file, and update
  the amount of cash in account, via a debit or a credit to the account */
  public:
    string findUsername(string user_file);
    string findAccType(string user_file);
    float findAvailableCredit(string user_file);
    void debitAccount(float value);
    void creditAccount(float value);
};

  /*Uses the user accounts file to get the username. The username is
  found by parsing the file, filtering for username and converting
  this data to a string value for username */
  string User::findUsername(string user_file){//tests user_file can hold value
    string filename =  string(user_file);

    username = filename; //this tests username attribute can hold value
    return username; //test for returning a string value
  }

  /*Uses the user accounts file to get the user account type. The account type is
  found by parsing the file, filtering for the account type and converting
  this data to a string value for account type. */
  string User::findAccType(string user_file){

      return "";
  }

  /*Uses the user accounts file to retrieve the availabe credit for the user.
  The available credit is found by parsing the file, filtering for user credit
  and returning the data as a float value indicating the amount available. */
  float User::findAvailableCredit(string user_file){


    return 0.0;
  }

  /*Increases the amount of credit available to the user by adding value,
  specificed through a refund, or add creadit transaction. */
  void User::debitAccount(float value){
      acc_amount += value;
  }

  /*Decreases the amount of credit available to the user by substracting value,
  specificed through a refund, or add creadit transaction. */
  void User::creditAccount(float value){
      acc_amount -= value;
  }

  int main(){

    User newUser; // creates a new user
    string name = "sohail";
    string theUser = newUser.findUsername(name);//calls findUsername using user file
    cout<<"The new user with username " <<theUser <<"\n";
  }
