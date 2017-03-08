#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "UserInteraction.h"
#include "User.h"
#include "math.h"

using namespace std;
User user;

//sets the user object for access to account type and username
void setUser(User u) {
    user = u;
}

//walks user through account creation proccess
void createUI() {
    string username ="", user_type = "II";
    float user_debit = -1;
    int  count = 0;

    //Prompts admin for username, user type, and credit amount

    while(username.length()==0 || username.length()>15){
      if(count == 0)
        cout<<"Enter a username (1-15 characters): ";
      else{
        cout<<"Invalid: characters violate constraint\n";
        return;
      }
      cin>>username;
      bool existUser = user.findUsername(username); //true: existing username, false: new username
      if(existUser){
        username = "";
        continue;
      }
      count++;
    }
    count = 0;
    while(user_type != "AA"){
       if(user_type == "AA" || user_type == "FS" || user_type == "BS"
                  || user_type == "SS"){
                    break;
                  }
       if(count == 0)
          cout<<"Enter type of user ('AA', 'FS', 'BS', 'SS'): ";
       else{
         cout<<"Invalid: user type not recognized\n";
         return;
       }
       cin>>user_type;
       count++;
    }
    count = 0;
    while(user_debit < 0 || user_debit >= 1000000){
       if(count == 0)
          cout<<"Enter a credit amount (0-999999.99): ";
       else{
         cout<<"Invalid credit amount\n";
         return;
       }
       cin>>user_debit;
       count++;
    }

    cout<<"Creating user with username: "<<username <<", type: "
    <<user_type <<", debit amount $" <<user_debit<<"\n"; //Successful create of new user

    ofstream daily_transactions_file("Daily_Transactions.txt");
    while(username.length() < 15){
        username += " ";
    }
    ostringstream ss;
    ss << (roundf(user_debit * 100) / 100);
    string deb_string(ss.str());
    bool dot = false;
    for(int i = 0; i < deb_string.length(); i++) {
        if(deb_string[i] == '.') {
            int left = 2 - (deb_string.length()-i);
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
    //need to do transaction stuff in other file, also need to check if user with this name exists
    daily_transactions_file <<"01 "<<username<<" "<<user_type<<" "<<deb_string;
    cout<<"Created user Successfully\n";
}

//asks user for information needed for adding credit
void addCreditUI(){


}

//asks user for information needed to refund the buyer
void refundUI(){
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
void buyUI(){

}

//asks user for information needed to sell tickets
void sellUI(){

}

//asks user for information needed to delete a user.
void deleteUserUI(){
   string username;

   cout<<"Enter a username: ";
   cout<<username;
   //delete user from user accounts
   cout<<"delete success";

}
