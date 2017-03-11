
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
#include <string>
#include <sstream>
#include "User.h"
#include <fstream>
#include "math.h"

using namespace std;

  //sets the username of a User, when create is issued
  void User::setUsername(string new_user){
    this->username = new_user;
  }

    //gets the username of a User, when needed in transactions
  string User::getUsername(){
    return this->username;
  }

  //sets the user account type for a User, when create is issued
  void User::setUserType(string user_type){
    this->user_acc_type = user_type;
  }

    //gets the user account type of a User, when needed in transactions
  string User::getUserType(){
    return this->user_acc_type;
  }

  //sets the user amount for a User
  void User::setUserAmount(double amount){
    this->acc_amount = amount;
  }

    //gets the user amount of a User, when needed in transactions
  double User::getUserAmount(){
    return this->acc_amount;
  } /* */

  /*Uses the user accounts file to get the username. The username is
  found by parsing the file, filtering for username and converting
  this data to a string value for username */
  bool User::findUsername(string username){//tests user_file can hold value
    ifstream infile("CurrentUsers.txt");
    string currUser, amount, user_type;

    while(infile >> currUser >> user_type >> amount ){
      if (username == currUser){
        return true;
      }
    }
    return false;
  }
  
  bool User::setUser(string username){
    ifstream infile("CurrentUsers.txt");
    string currUser, user_type;
    double amount;

    while(infile >> currUser >> user_type >> amount){
        if (username == currUser){
            this->setUsername(username);
            this->setUserType(user_type);
            this->setUserAmount(amount);
            return true;
        } //clear variables
    }
    return false;
  }

  /*Uses the user accounts file to get the user account type. The account type is
  found by parsing the file, filtering for the account type and converting
  this data to a string value for account type. */
  string User::findAccType(string username){
      //defaults for now
      if (username == "admin") {
        return "AA";
      }
      else {
        return "FS";
      }
  }

  /*Uses the user accounts file to retrieve the availabe credit for the user.
  The available credit is found by parsing the file, filtering for user credit
  and returning the data as a double value indicating the amount available. */
  double User::findAvailableCredit(string username){
    return 0.0;
  }

  /*Increases the amount of credit available to the user by adding value,
  specificed through a refund, or add creadit transaction. */
  void User::debitAccount(double value){
      this->acc_amount += value;
  }

  /*Decreases the amount of credit available to the user by substracting value,
  specificed through a refund, or add creadit transaction. */
  void User::creditAccount(double value){
      this->acc_amount -= value;
  }
  
  //converts the credit to the format needed for transaction file
  std::string User::convertCredit(double v){
      ostringstream ss;
      ss << (round(v * 100) / 100);
      string deb_string(ss.str());
      bool dot = false;
      for(int i = 0; i < deb_string.length(); i++) {
          if(deb_string[i] == '.') {
              int left = 3 - (deb_string.length()-i);
              for(int j = 0; j < left; j++) {
                  deb_string += "0";
              }
              dot = true;
              break;
          }
      }
      if(!dot) {
          deb_string += ".00";
      }
      while(deb_string.length() < 9){
          deb_string.insert(deb_string.begin(),'0');
      }
      return deb_string;
  }
  
  //converts username to the format for transaction file
  std::string User::convertName(std::string u){
    while(u.length() < 15){
        u += " ";
    }
    return u;
  }
