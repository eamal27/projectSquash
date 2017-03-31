JFLAGS = -g
JC = javac
JVM= java
FILE=
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java
CLASSES = \
	UpdateUserAccounts.java \
	ErrorLogs.java \
	ProcessAvailableTickets.java \
	ProcessCurrentUsers.java \
	Account.java \
	Ticket.java \
	ProcessAvailableTicketsTest.java \
	ProcessCurrentUsersTest.java \
	UpdateUserAccountsTest.java \
	AccountTest.java \
	TicketTest.java \

MAIN = UpdateUserAccounts

TESTS = \
	UpdateUserAccountsTest \
	ProcessCurrentUsersTest \
	ProcessAvailableTicketsTest \
	AccountTest \
	TicketTest \

default: classes

classes: $(CLASSES:.java=.class)

run: classes
	$(JVM) $(MAIN)

clean:
	$(RM) *.class

test: classes
	$(JVM) org.junit.runner.JUnitCore $(TESTS)
