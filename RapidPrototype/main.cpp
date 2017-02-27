

#include <iostream>
#include <string>
#include "System.h"
#include "Transaction.h"
#include "TicketInventory.h"
#include "User.h"
#include "UserInteraction.h"

using namespace std;

int main(int argc, char *argv[]){

	//verify that the username used to login is a current user
	User new_user; // creates a new user
	string name = "sohail";
	string theUser = new_user.findUsername(name);//calls findUsername using user file
	cout<<"The new user with username " <<theUser <<"\n";

	//checks that login and logout output appropriate messages
	string message = initialLogin("login");
	cout<<message <<"\n";
	string logoutMsg = logout();
	cout<<logoutMsg<<"\n";

	UserInteraction create_user;
	create_user.createUI();


	return 0;
}
