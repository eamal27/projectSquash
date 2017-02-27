#include <iostream>
#include <string>
#include "UserInteraction.h"
#include "User.h"

using namespace std;
User user;

//sets the user object for access to account type and username
void setUser(User u) {
    user = u;
}

//walks user through account creation proccess
void UserInteraction::createUI() {
    string username, user_type;
    float user_credit;

    //Prompts admin for username, user type, and credit amount
    cout<<"Enter a username: ";
    cin>>username;
    cout<<"Enter type of user: ";
    cin>>user_type;
    cout<<"Enter a credit amount: ";
    cin>>user_credit;
    cout<<"User created with username: "<<username <<", type: "
    <<user_type <<", creidt amount $" <<user_credit<<"\n"; //Successful create of new user

    //Set the inforamtion for new user in User accounts
    User new_user;
    new_user.setUsername(username);
    new_user.setUserType(user_type);
    new_user.debitAccount(user_credit);

    string create_username = new_user.username;
    cout<<"\nThe new created user has username " <<create_username <<"\n";
}

//asks user for information needed for adding credit
void UserInteraction::addCreditUI(){


}

//asks user for information needed to refund the buyer
void UserInteraction::refundUI(){
  string buyer_username, seller_username;
  float refund_amount;

  //promts user for information
  cout<<"Enter username of buyer: ";
  cout<<buyer_username;
  cout<<"Enter username of seller: ";
  cout<<seller_username;
  cout<<"Enter refund amount: ";
  cout<<refund_amount;
  cout<<"Refund successful.";

}

//asks user for information needed for a purchase of tickets
void UserInteraction::buyUI(){

}

//asks user for information needed to sell tickets
void UserInteraction::sellUI(){

}

//asks user for information needed to delete a user.
void UserInteraction::deleteUserUI(){
  string username;

   cout<<"Enter a username: ";
   cout<<username;
   //delete user from user accounts
   cout<<"delete success";

}
