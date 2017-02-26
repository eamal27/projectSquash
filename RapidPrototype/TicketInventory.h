#ifndef TICKETINVENTORY_H_
#define TICKETINVENTORY_H_

class TicketInventory{

	int quantity;
	float ticket_price;
	std::string seller_name;
	std::string event_title;

	public:
		float totalPrice(int quantity, float ticket_price);
		std::string findSeller(std::string ticket_file);
		std::string findEvent(std::string ticket_file);
		int numberTickets(std::string ticket_file);
};

#endif