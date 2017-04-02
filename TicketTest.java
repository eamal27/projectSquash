import junit.framework.TestCase;
import org.junit.Assert;
import org.junit.Test;

public class TicketTest extends TestCase {

    public String expected_event = "SomeEvent";
    public String expected_seller = "caleb";
    public int expected_tickets = 10;
    public float expected_ticketPrice = 9.99f;
    public Ticket newTicket = new Ticket(expected_event, expected_seller,
     expected_tickets, expected_ticketPrice);     

    @Test
    public void testGetEventName() throws Exception {
        String eventTitle = newTicket.getEventName(); 

        assertEquals(expected_event, eventTitle);
    }

    @Test
    public void testGetSellerUsername() throws Exception {
        String seller_username = newTicket.getSellerUsername();

        assertEquals(expected_seller, seller_username);
    }

    @Test
    public void testGetTicketCount() throws Exception {
        int num_tickets = newTicket.getTicketCount(); 
        assertEquals(expected_tickets, num_tickets);
    }

    @Test
    public void testGetTicketPrice() throws Exception {
        float ticket_price = newTicket.getTicketPrice();
        assertEquals(expected_ticketPrice, ticket_price);
    }

}