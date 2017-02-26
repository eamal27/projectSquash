

#include <iostream>
#include <string>
#include "System.h"
#include "Transaction.h"
#include "TicketInventory.h"
#include "User.h"
#include "UserInteraction.h"

using namespace std;

int main(int argc, char *argv[]){
	User newUser; // creates a new user
	string name = "sohail";
	string theUser = newUser.findUsername(name);//calls findUsername using user file
	cout<<"The new user with username " <<theUser <<"\n";

	string message = initialLogin("login");
	cout<<message <<"\n";
	string logoutMsg = logout();
	cout<<logoutMsg<<"\n";

	return 0;
}