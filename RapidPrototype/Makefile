CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LFLAGS = 
LIBS = 
SOURCES = main.c System.c TicketInventory.c Transaction.c User.c UserInteraction.c
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = prototype.exe
.PHONY: clean help

prototype.exe : main.o System.o TicketInventory.o Transaction.o User.o UserInteraction.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

cleanup:
	rm -f $(OBJECTS) *~

help:
	@echo "Valid targets:"
	@echo "  all:    generates all binary files"
	@echo "  clean:  removes .o and .exe files"
