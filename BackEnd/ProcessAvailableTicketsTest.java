import junit.framework.TestCase;

import java.util.ArrayList;

public class ProcessAvailableTicketsTest extends TestCase {

    ProcessAvailableTickets availableTickets = new ProcessAvailableTickets();

    public void testParseTickets() throws Exception {
        availableTickets.ParseTickets("TestTicketsFiles/zero_line.txt");
        //array should be empty since no tickets in end_line.txt
        assertEquals(0, availableTickets.tickets.size());

        //loop coverag, while loop in ParseTickets
        availableTickets.ParseTickets("TestTicketsFiles/blank_line.txt");
        //array should be empty since no tickets in end_line.txt
        assertEquals(0, availableTickets.tickets.size());

        availableTickets.ParseTickets("TestTicketsFiles/one_line.txt");
        String eventName = availableTickets.tickets.get(0).eventName;
        assertEquals("bbq", eventName);

        availableTickets.ParseTickets("TestTicketsFiles/two_line.txt");
        String first_event = availableTickets.tickets.get(0).eventName;
        String second_event = availableTickets.tickets.get(1).eventName;
        assertEquals("Event1", first_event);
        assertEquals("Event2", second_event);

        availableTickets.ParseTickets("TestTicketsFiles/many_line.txt");
        String event1 = availableTickets.tickets.get(0).eventName;
        String event2 = availableTickets.tickets.get(1).eventName;
        String event3 = availableTickets.tickets.get(2).eventName;
        assertEquals("Event1", event1);
        assertEquals("Superbowl", event2);
        assertEquals("uoit", event3);

    }

    public void testGetTickets() throws Exception {
        availableTickets.ParseTickets("TestTicketsFiles/one_line.txt");
        ArrayList<Ticket> tickets = availableTickets.getTickets();
        assertNotNull(tickets);
    }

}