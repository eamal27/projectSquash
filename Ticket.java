/**
 * Created by eamal27 on 2017-03-16.
 */
public class Ticket {
    String eventName;
    String sellerUsername;
    int ticketCount;
    float ticketPrice;

    public Ticket(String eventName, String sellerUsername, int ticketCount, float ticketPrice) {
        this.eventName = eventName;
        this.sellerUsername = sellerUsername;
        this.ticketCount = ticketCount;
        this.ticketPrice = ticketPrice;
    }
}
