
#include <iostream>
#include <string>
#include "TicketInventory.h"

using namespace std;

	int quantity;
	float ticket_price;
	std::string seller_name;
	std::string event_title;

	float totalPrice(int quantity, float ticket_price){

	}

	std::string findSeller(std::string ticket_file){

	}

	std::string findEvent(std::string ticket_file){


	}

	//Finds the number of tickets from the ticket file, and returns the value.
	int numberTickets(std::string ticket_file){
		int value_from_file = 3;

		/*will need to extract the number of tickets from the ticket file
		using a loop that parses to end of file. The line will be searched for 
		pattern of the quantity of tickets in the file. */
		
		quantity = value_from_file;

		return quantity;
	}