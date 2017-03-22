<<<<<<< HEAD


public class ProcessAvailableTickets{
	
	public ArrayList<int> number_tickets;
	public ArrayList<String> event_title;


	public ProcessAvailableTickets(){
		
	}

	public static ArrayList<int> determineTicketsLeft(){

		return number_tickets;
	}

	public static ArrayList<String> determineEvent(){

		return event_title;
=======
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class ProcessAvailableTickets{

	public ArrayList<Ticket> tickets;


	public ProcessAvailableTickets(){

	}

    //Extracts the event name, username, number of tickets, and price from the 
    //tickets file. These values from the file are then passed to the Ticket class
    public void ParseTickets(){
                // initialize array
        this.tickets = new ArrayList<Ticket>();

        // read in old tickets files
        File file = new File("tickets.log");
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) { //reads file line by line
                if (!line.equals("END")) {
                    //parse for relevant information from the ticket file
                    String eventname = line.substring(0,25).trim();
                    String username = line.substring(26,41).trim();
                    int num_tickets = Integer.parseInt(line.substring(42,45).trim());
                    float price = Float.parseFloat(line.substring(46,52).trim());
                    this.tickets.add(new Ticket(eventname,username,num_tickets,price));
                }
            }
        }catch(Exception e){
            System.out.println("Could not find file.");
        }

    }

	// return list of tickets
	public ArrayList<Ticket> getTickets(){

		return this.tickets;
>>>>>>> bb064c088a31e86a25980814ba2d7453e7b8212f
	}

}
