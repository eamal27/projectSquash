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
	Test.java \

MAIN = UpdateUserAccounts

default: classes

classes: $(CLASSES:.java=.class)

run: classes
	$(JVM) $(MAIN)

clean:
	$(RM) *.class

test: classes
	$(JVM) org.junit.runner.JUnitCore Test
