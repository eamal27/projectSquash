
#include <iostream>
#include <string>
#include "TicketInventory.h"

using namespace std;

float TicketInventory::totalPrice(int quantity, float ticket_price){
	return 0;
}

std::string TicketInventory::findSeller(std::string ticket_file){
	return "";
}

std::string TicketInventory::findEvent(std::string ticket_file){
	return "";
}

//Finds the number of tickets from the ticket file, and returns the value.
int TicketInventory::numberTickets(std::string ticket_file){
	int value_from_file = 3;

	/*will need to extract the number of tickets from the ticket file
	using a loop that parses to end of file. The line will be searched for 
	pattern of the quantity of tickets in the file. */

	this->quantity = value_from_file;

	return this->quantity;
}