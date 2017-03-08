
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
#include "User.h"
#include <fstream>

using namespace std;

  std::string filename; //user accounts file
  std::string username; //the User's username for the account
  std::string user_acc_type; //is the user account type (eg. full-standard, admin, etc.)
  float acc_amount; //is the current amount in user's account

  //sets the username of a User, when create is issued
  void User::setUsername(string new_user){
    username = new_user;
  }

    //gets the username of a User, when needed in transactions
  string User::getUsername(){
    return username;
  }

  //sets the user account type for a User, when create is issued
  void User::setUserType(string user_type){
    user_acc_type = user_type;
  }

    //gets the user account type of a User, when needed in transactions
  string User::getUserType(){
    return user_acc_type;
  }

/*  //sets the user amount for a User
  void User::setUserAmount(string user_amount){

    acc_amount = atof(user_amount.c_str());
  }
*/
    //gets the user amount of a User, when needed in transactions
  float User::getUserAmount(){
    return acc_amount;
  } /* */

  /*Uses the user accounts file to get the username. The username is
  found by parsing the file, filtering for username and converting
  this data to a string value for username */
  bool User::findUsername(string username){//tests user_file can hold value
    ifstream infile("CurrentUsers.txt");
    string currUser;

    while(infile >> currUser >> user_acc_type >> acc_amount ){
      User the_user;
      if (username == currUser){
        setUsername(username);
        setUserType(user_acc_type);
        //setUserAmount(acc_amount);
        return true;
      }

    }

    return false; //test for returning a string value
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
  and returning the data as a float value indicating the amount available. */
  float User::findAvailableCredit(string username){


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
