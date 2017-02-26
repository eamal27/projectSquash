.PHONY: clean run

out : main.cpp System.cpp TicketInventory.cpp Transaction.cpp User.cpp UserInteraction.cpp
	g++ -g main.cpp System.cpp TicketInventory.cpp Transaction.cpp User.cpp UserInteraction.cpp -std=c++11 -lpthread

all : out

clean:
	rm -f a.out
