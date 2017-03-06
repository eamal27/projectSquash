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
void createUI() {
    string username ="", user_type = "II";
    float user_credit = 0;
    int  count = 0;

    //Prompts admin for username, user type, and credit amount

    while(username.length()==0 || username.length()>15){
      if(count == 0)
        cout<<"Enter a username (0-15 characters): ";
      else
        cout<<"Invalid: characters violate constraint\n Re-enter username (0-15 characters): ";
      cin>>username;
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
         cout<<"Invalid: user type not recognized\n Re-ennter user type ('AA', 'FS', 'BS', 'SS'): ";
       }
       cin>>user_type;
       count++;
    }
    count = 0;
    while(user_credit ==0|| user_credit < 0 || user_credit> 999999){
       if(count == 0)
          cout<<"Enter a credit amount (1-999999): ";
       else{
         cout<<"Invalid credit amount\n Re-ennter credit amount (1-999999): ";
       }
       cin>>user_credit;
       count++;
    }

    cout<<"Creating user with username: "<<username <<", type: "
    <<user_type <<", creidt amount $" <<user_credit<<"\n"; //Successful create of new user

    //Set the inforamtion for new user in User accounts
    User new_user;
    new_user.setUsername(username);
    new_user.setUserType(user_type);
    new_user.debitAccount(user_credit);

    string create_username = new_user.username;
    cout<<"Created user " <<create_username <<" Successfully\n";
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
