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
	Account.java \
	ProcessAvailableTickets.java \
	ProcessCurrentUsers.java \
	Ticket.java \
	ProcessAvailableTicketsTest.java \
	ProcessCurrentUsersTest.java \
	UpdateUserAccountsTest.java \

MAIN = UpdateUserAccounts

TESTS = \
	UpdateUserAccountsTest \
	ProcessCurrentUsersTest \
	ProcessAvailableTicketsTest \

default: classes

classes: $(CLASSES:.java=.class)

run: classes
	$(JVM) $(MAIN)

clean:
	$(RM) *.class

test: classes
	$(JVM) org.junit.runner.JUnitCore $(TESTS)
