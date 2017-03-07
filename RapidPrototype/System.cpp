
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

User new_user;

int main(int argc, char *argv[]){

	//verify that the username used to login is a current user


	cout<<"Welcome to the Ticket Selling Service System\n";
	//Command: login, logout, create, quit
	bool quit = false;
	int start = 1;
	while(!quit) {
		bool logged = false;
		string command, theUser, type;
		while(!logged) {

			if(start == 1 || command == "cmd"){
				cout<<"System Commands:\n"<<"login\t\tlogout\t\tquit\ncreate\t\tcmd\n";
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
				type = new_user.getUserType();
				cout<<"login successful\n";  //The abover findUsername, findAccType shoudl
																	//be done in initial login function
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
			logged = initiateTransaction(type,command); //tells the system the users account type and entered command
			//this way it can determine if it should allow said command.
			//only working commands are logout and create
		}
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
		if(verifyUsername(username))
			return true; //only returns true if they login, for now it assumes whatever login they enter is ok
		else{
			cout<<"Invalid: username not a current user or violates length constraint\n";
			return false;
		}
	}
	else if(systemCmd == "logout"){//logout command fails
		cout<<"Invalid: can not logout before logging in\n";
		return false;
	}
	//any tranaction other than a login fails
	else if(systemCmd == "create" || systemCmd == "delete" || systemCmd == "sell" ||
	 systemCmd == "buy" || systemCmd == "refund" || systemCmd == "addcredit"){
		cout<<"Invalid: need to login first before issuing a transaction\n";
		return false;
	}
	else { //otherwise user entered non valid command
		cout<<"Invalid: not a system command\n";
		return false;
	}
}

bool verifyUsername(string username){
	//checks that username is not blank and is at most 15 characters
	if(username.length()==0 || username.length()>15){
		return false;
	}
	else if(new_user.findUsername(username)){

		return true;
	}
	else{
		return false;
	}

	return false;
}

/*Checks whether a particular type of user can issue a specific transaction. Transaction such as create
and delete can only be issued by a user of admin type. */
bool initiateTransaction(string user_type, string transactin_name){

	if(user_type == "AA" && (transactin_name =="create" || transactin_name =="delete")){
		if(transactin_name =="create") {
			createUI();
		}
		return true;
	}
	else if(user_type != "AA" && (transactin_name =="create" || transactin_name =="delete")){
		cout<<"Insufficient permission\n";
		return true;
	}
	else if(transactin_name =="logout"){
		return logout();
	}
	else {
		cout<<"Invalid command\n";
		return true;
	}
}

/*Allows the user to logout, if contraints are met. Can not logout if user is
not logged in. */
bool logout(){
	cout<<"logout successful\n";
	//will change the current user in UserInteraction to null;
	return false;
}
