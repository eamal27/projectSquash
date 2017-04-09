/**
 * Created by eamal27 on 2017-03-16.
 */
public class Ticket {
    public String eventName;
    public String sellerUsername;
    public int ticketCount;
    public float ticketPrice;

    public Ticket(String eventName, String sellerUsername, int ticketCount, float ticketPrice) {
        this.eventName = eventName;
        this.sellerUsername = sellerUsername;
        this.ticketCount = ticketCount;
        this.ticketPrice = ticketPrice;
    }

    public String getEventName(){
        return eventName;
    }

    public String getSellerUsername(){
        return sellerUsername;
    }    

    public int getTicketCount(){
        return ticketCount;
    }

    public float getTicketPrice(){
        return ticketPrice;
    }

}


