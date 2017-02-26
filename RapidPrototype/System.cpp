
/*
Login Class

*/

#include <iostream>
#include <string>
#include "System.h"

using namespace std;

	/*This is the first time user interacts with system. To enter the system
	need to use login command. The system command is taken as a parameter then checked
	through multiple conditions on which command it has initiated. Only the login command
	will be accpeted, for user to be successfully logged into the system.*/
bool logged_in;

	 string initialLogin(string systemCmd){
		string loginMessage;
		
		if(systemCmd == "login"){
			loginMessage = "login successful";
			logged_in = true;
		}
		else if(systemCmd == "logout"){//logout command fails
			loginMessage = "Invalid: can not logout before logging in";
		}
		//any tranaction other than a login fails
		else if(systemCmd == "create" || systemCmd == "delete" || systemCmd == "sell" ||
		 systemCmd == "buy" || systemCmd == "refund" || systemCmd == "addcredit"){
			loginMessage = "Invalid: need to login first before issuing a transaction";
		}
		return loginMessage; 
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
		
		if(user_type == "admin" && transactin_name =="create" || 
			user_type == "admin" && transactin_name =="delete"){

			return true;
		}
		else if(user_type != "admin" && transactin_name =="create" || user_type != "admin" 
			&& transactin_name =="create"){
			return false;
		}


		return false;		
	}		

	/*Allows the user to logout, if contraints are met. Can not logout if user is
	not logged in. */
	string logout(){

		string message = "";

		if(logged_in == true){ //User is logged in
			message = "logout successful";
			logged_in = false;//change to logout
			return message;
		}
		else {//user not logged in
			message = "Invalid: can not logout";
			return message;
		}
		return message;
	}

