

#include <iostream>
#include <string>
#include "System.h"
#include "Transaction.h"
#include "TicketInventory.h"
#include "User.h"

using namespace std;

int main(int argc, char *argv[]){

	//verify that the username used to login is a current user
	User new_user; // creates a new user

	cout<<"Welcome to the Ticket Selling Service System\n";
	bool logged = false;
	string command;
	while(!logged) {//when you are logged in
		cout<<"Enter system command:\n";
		cin>>command;
		logged = initialLogin(command); //later we will then check their username efore exiting loop
		//but for now we assume any name is correct
	}
	string name;
	cin>>name;
	string theUser = new_user.findUsername(name);//calls findUsername using user file
	string type = new_user.findAccType(name); //finds associated account type
	/*currently the username is also the type for the user. Type 'admin' as username
	 to issue a 'create' transsaction.
	 for now all accounts besides "admin" are FS */
	cout<<"Login Success\n";

	while(logged) {
		cout<<"Type the transaction to carry out:\n";
		cin>>command;
		logged = initiateTransaction(type,command); //tells the system the users account type and entered command
		//this way it can determine if it should allow said command.
		//only working commands are logout and create
	}
	cout<<"Thank you for using the Ticket Selling Service System\n";
	return 0;
}
