

#include <iostream>
#include <string>
#include "System.h"
#include "Transaction.h"
#include "TicketInventory.h"
#include "User.h"

using namespace std;

int main(){


	User newUser; // creates a new user
	string name = "sohail";
	string theUser = newUser.findUsername(name);//calls findUsername using user file
	cout<<"The new user with username " <<theUser <<"\n";

	System newSystem;

	string message = newSystem.initialLogin("login");
	cout<<message <<"\n";
	string logoutMsg = newSystem.logout();
	cout<<logoutMsg<<"\n";

	return 0;
}