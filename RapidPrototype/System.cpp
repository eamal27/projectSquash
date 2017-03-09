
/*
Login Class

*/

#include <iostream>
#include <string>
#include "System.h"
#include "Transaction.h"
#include "TicketInventory.h"
#include "User.h"
#include "UserInteraction.h"
#include <fstream>

using namespace std;

/*This is the first time user interacts with system. To enter the system
need to use login command. The system command is taken as a parameter then checked
through multiple conditions on which command it has initiated. Only the login command
will be accpeted, for user to be successfully logged into the system.*/

User user_logged;

int main(int argc, char *argv[]){

	//verify that the username used to login is a current user


	cout<<"Welcome to the Ticket Selling Service System\n";
	//Command: login, logout, create, quit
	bool quit = false;
	int start = 1;
	string temp_file = "temp_file.txt";

	while(!quit) {
		bool logged = false;
		string command;
		while(!logged) {

			if(start == 1 || command == "cmd"){
				cout<<"System Commands:\n"<<"login\t\tlogout\t\tquit\ncreate\t\t"
				<<"addcredit\tcmd\n";
				start++;
			}
			cout<<"Enter system command:\n";
			cin>>command;

			if (command == "quit") {
				quit = true;
				cout<<"session terminated\n";
				break;
			}

			logged = initialLogin(command); //login checks for username

			if(logged) {
    			cout<<"login successful\n"; 
			}
		}
		//for now all accounts besides "admin" are FS

		while(logged) {
			cout<<"Type the transaction to carry out:\n";
			cin>>command;
			if (command == "quit") {
				quit = true;
				cout<<"Session terminated\n";
				break;
			}
			logged = initiateTransaction(command); //tells the system the users account type and entered command
			//this way it can determine if it should allow said command.
			//only working commands are logout and create
		}
		start--;
	}
	cout<<"Thank you for using the Ticket Selling Service System\n";
	return 0;
}

bool initialLogin(string systemCmd){
	string loginMessage;
	string username;
	if(systemCmd == "login"){
		cout<<"Please enter username:\n";
		cin>>username;
		if(verifyUsername(username)) {
		    user_logged.setUsername(username);
		    user_logged.setUserType(user_logged.findAccType(username));
			return true; //only returns true if they login, for now it assumes whatever login they enter is ok
		} else{
			cout<<"Invalid: username not a current user or violates length constraint\n";
		}
	} else if(systemCmd == "logout"){//logout command fails
		cout<<"Invalid: can not logout before logging in\n";
	} else if(systemCmd == "create" || systemCmd == "delete" || systemCmd == "sell" ||
	 systemCmd == "buy" || systemCmd == "refund" || systemCmd == "addcredit"){
		cout<<"Invalid: need to login first before issuing a transaction\n";
	} else { //otherwise user entered non valid command
		cout<<"Invalid: not a system command\n";
	}
	return false;
}

bool verifyUsername(string username){
	//checks that username is not blank and is at most 15 characters
	if(username.length()==0 || username.length()>15){
		return false;
	}
	else if(user_logged.findUsername(username)){
		return true;
	}
	else{
		return false;
	}
}

/*Checks whether a particular type of user can issue a specific transaction. Transaction such as create
and delete can only be issued by a user of admin type. */
bool initiateTransaction(string transactin_name){
    string user_type = user_logged.getUserType();
	if(transactin_name =="logout"){
		return logout();
	} else if(user_type == "AA"){
		if(transactin_name =="create") {
			createUI();
		} else if(transactin_name=="addcredit"){
			addCreditUI();
		}
	} else if(user_type != "AA" && (transactin_name =="create" || transactin_name =="delete")){
		cout<<"Insufficient permission\n";
	} else {
		cout<<"Invalid command\n";
	}
	return true;
}

/*Allows the user to logout, if contraints are met. Can not logout if user is
not logged in. */
bool logout(){
	cout<<"logout successful\n";
	ifstream reader;
	ofstream writer;
	reader.open("temp_file.txt");
	bool exists = true;
	int num = 1;
	while(exists) {
	    ifstream f("Daily_Transactions" + to_string(num) + ".txt");
	    if (!f.good()) {
	        exists = false;
	        f.close();
	    } else {
	        num++;
	    }
	}
	writer.open("Daily_Transactions" + to_string(num) + ".txt");
	while(!reader.eof()){
	    char c = reader.get();
	    if(!reader.eof()){ //don't want to read last character
	        writer << c;
	    }
	}
	writer << "00 " << user_logged.convertName(user_logged.getUsername()) << " " << user_logged.getUserType()
	       << " " << user_logged.convertCredit(user_logged.getUserAmount()) << "\n";
	writer.close();
	reader.close();
	writer.open("temp_file.txt"); //too clear it
	writer.close();
	return false;
}
