

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
	while(!logged) {
		cout<<"Enter system command:\n";
		cin>>command;
		logged = initialLogin(command);
	}
	string name;
	cin>>name;
	string theUser = new_user.findUsername(name);//calls findUsername using user file
	string type = new_user.findAccType(name);
	cout<<"Login Success\n";
	
	while(logged) {
		cout<<"Type the transaction to carry out:\n";
		cin>>command;
		logged = initiateTransaction(type,command);
	}
	cout<<"Thank you for using the Ticket Selling Service System\n";
	return 0;
}
