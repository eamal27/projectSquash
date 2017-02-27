
/*
Login Class

*/

#include <iostream>
#include <string>
#include "System.h"
#include "UserInteraction.h"

using namespace std;

/*This is the first time user interacts with system. To enter the system
need to use login command. The system command is taken as a parameter then checked
through multiple conditions on which command it has initiated. Only the login command
will be accpeted, for user to be successfully logged into the system.*/

bool initialLogin(string systemCmd){
	string loginMessage;

	if(systemCmd == "login"){
		cout<<"Please enter username:\n";
		return true;
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
	else {
		cout<<"Invalid: not a system command\n";
		return false;
	}
}

bool verifyUsername(string username){

	//checks that username is not blank and is at most 15 characters
	if(username.length()==0 || username.length()>15){
		return false;
	}
	else{
		return true;
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
