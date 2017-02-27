.PHONY: clean run

out : System.cpp TicketInventory.cpp Transaction.cpp User.cpp UserInteraction.cpp
	g++ -g System.cpp TicketInventory.cpp Transaction.cpp User.cpp UserInteraction.cpp -std=c++11 -lpthread

all : out

clean:
	rm -f a.out
