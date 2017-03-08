#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "UserInteraction.h"
#include "User.h"
#include "math.h"

using namespace std;
User user;
int file_num = 1;
ostringstream file_new;


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
    while(user_debit < 0 || user_debit >= 999999){
       if(count == 0)
          cout<<"Enter a credit amount (0-999999): ";
       else{
         cout<<"Invalid credit amount\n";
         return;
       }
       cin>>user_debit;
       count++;
    }

    cout<<"Creating user with username: "<<username <<", type: "
    <<user_type <<", debit amount $" <<user_debit<<"\n"; //Successful create of new user

    string filename = "temp_file.txt";
    ofstream temp_file(filename, ios::app);
    username = user.convertName(username);
    string deb_string = user.convertCredit(user_debit);

    temp_file <<"01 "<<username<<" "<<user_type<<" "<<deb_string<<"\n";
    cout<<"Created user Successfully\n";
}

//asks user for information needed for adding credit
void addCreditUI(){
  int count = 0;
  string username = "";//to enter loop
  float user_debit;

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
      continue;
    }
    count++;
  }
  count = 0;
  while(user_debit < 0 || user_debit >= 1000000){
     if(count == 0)
        cout<<"Enter a credit amount (0-1000000): ";
     else{
       cout<<"Invalid credit amount\n";
       return;
     }
     cin>>user_debit;
     count++;
  }

  user.setUsername(username);
  user.debitAccount(user_debit);


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
  string sell_title = "";
  int num_tickects = 0, count =0;
  float sale_price = 0;

  while(sell_title.length() == 0 || sell_title.length()>25){
    if(count == 0)
      cout<<"Enter title (1-15 characters): ";
    else{
      cout<<"Invalid: characters violate constraint\n";
      return;
    }
    cin>>sell_title;
    count++;
  }
  count = 0;
  while(sale_price<1 || sale_price > 999.99){
    if(count == 0)
      cout<<"Enter number of tickects for sale (1-999.99): ";
    else{
      cout<<"Invalid: characters violate constraint\n";
      continue;
    }
  }
  count = 0;
  while(num_tickects<1 || num_tickects > 100){
    if(count == 0)
      cout<<"Enter number of tickects for sale (1-100): ";
    else{
      cout<<"Invalid: characters violate constraint\n";
      continue;
    }
    cin>>num_tickects;
  }


}

//asks user for information needed to delete a user.
void deleteUserUI(){
   string username;

   cout<<"Enter a username: ";
   cout<<username;
   //delete user from user accounts
   cout<<"delete success";

}
