
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FileReader;
import java.util.*;
import java.io.IOException;
import junit.framework.TestCase;

/*Merges changes that occured in the DailyTransaction file with the AvailableTickets file and the CurrentUserAccounts
file. The main method passes the required lists to the methods. Each method  */
public class UpdateUserAccounts extends TestCase{

    int transactionCode;
    float creditAmount;
    int numTickets;
    float priceTicket;
    String userType;
    String buyerUsername;
    String sellerUsername;
    String eventName;

    List<String> fmtone_username = new ArrayList<String>();
    List<String> fmtone_usertype = new ArrayList<String>();
    List<Float> fmtone_credit = new ArrayList<Float>();
    List<Integer> fmtone_code = new ArrayList<Integer>();

    ProcessAvailableTickets ticketHelper = new ProcessAvailableTickets();
    ArrayList<Ticket> tickets = new ArrayList<Ticket>();

	public UpdateUserAccounts(){
        // parse old tickets file and store ticket data
        ticketHelper.ParseTickets();
	}
    /* */
	public void testOne() {
			assertTrue(true);
	}
	public void testTwo() {
			assertTrue(true);
	}
	public void testThree() {
			assertTrue(true);
	}
	public void testFour() {
			assertTrue(true);
	}
    

	/**
	 *  Parses daily transaction file and populates the username_list and user_credit_list arrays
	 */
	public void dailyTransactionParse(){
		// parse merge daily transaction file	
		File file = new File("mergedDailyTransactions.log");
		try (BufferedReader br = new BufferedReader(new FileReader(file))) {
			String line;
			while ((line = br.readLine()) != null) {
				if (!line.equals("END")) {
					transactionCode = Integer.parseInt(line.substring(0,2).trim());//extracts the code for transaction
                    switch (transactionCode) { //parses in different formats based on the transaction code
                        case 1:
                            parseFormat1(line, transactionCode);
                            //createAccount();
                            break;
                        case 2:
                            parseFormat1(line, transactionCode);
                            //deleteAccount();
                            break;
                        case 3:
                            parseFormat3(line);
                            //sell();
                            break;
                        case 4:
                            parseFormat3(line);
                            //buy();
                            break;
                        case 5:
                            parseFormat2(line);
                            //refund();
                            break;
                        case 6:
                            parseFormat1(line, transactionCode);
                            //addCredit();
                            break;
                        default:
                            continue;
                    }
				}
			}
		}catch(Exception e){
			System.out.println("Could not find file.");
		}
	}


    private void parseFormat1(String line, int transactionCode) {
        buyerUsername = line.substring(3,18);
        userType = line.substring(19,21);
        creditAmount = Float.parseFloat(line.substring(22,31));
        System.out.println(transactionCode + " " + buyerUsername + " " + userType + " " + creditAmount);
        
        fmtone_code.add(transactionCode);
        fmtone_username.add(buyerUsername);
        fmtone_usertype.add(userType);
        fmtone_credit.add(creditAmount);
    }

    private void parseFormat2(String line) {
        buyerUsername = line.substring(3,18).trim();
        sellerUsername = line.substring(19,34).trim();
        creditAmount = Float.parseFloat(line.substring(35,44).trim());
        System.out.println(transactionCode + " " + buyerUsername + " " + sellerUsername + " " + creditAmount);
    }

    private void parseFormat3(String line) {
        eventName = line.substring(3,28).trim();
        sellerUsername = line.substring(29,44).trim();
        numTickets = Integer.parseInt(line.substring(45,48).trim());
        priceTicket = Float.parseFloat(line.substring(49,55).trim());
        System.out.println(transactionCode + " " + eventName + " " + sellerUsername + " " + numTickets + " " + priceTicket);
    }

    /*Uses the old user amount, and the change user amount lists from the ProcessCurrentUsers class, and the 
      ReadDailyTransaction class respectively. It updates the old user amount list with the change. The username
      index identifies which amount in list belongs to the username specified. */
	public void updateAmount(List<Float> old_user_amount, List<Float> change_user_amount, int user_index){

		float old_amount = old_user_amount.get(user_index);
		float new_amount = old_amount + (change_user_amount.get(user_index));
		setUserAmount(new_amount);

	}	

	//sets the updated amount to the credit amount list, to store in list
	public void setUserAmount(float new_amount){
		
	}

	/*Uses the number of tickets list from the Available Tickets file and the list of left over available tickets
	  from the DailyTransaction file. It creates a new list after adding or substracting from the old available
	  tickets list. The event_index will be used to idenitify the correct event to event.*/
	public void updateNumberTickets(ArrayList<Integer> old_number_tickets, List<Integer> change_number_tickets, int event_index){

	}

	/*Takes in the username_list, and gets the stored new credit amount_list then writes to the Current Accounts file
	replacing the old contents */
	public void writeUsers(){
        ProcessCurrentUsers current_users = new ProcessCurrentUsers();
        current_users.readUserAccounts();
        List<String> usernames =  current_users.getUsernameList();
        List<String> user_type = current_users.getUserType();
        List<Double> user_amount = current_users.getUserAmount();


        try{
            File curr_user_accounts = new File("CurrentUserAccounts.txt");
            if(!curr_user_accounts.exists()){
                curr_user_accounts.createNewFile();
            } 
            FileWriter write_file = new FileWriter(curr_user_accounts.getName(), true);
            BufferedWriter buffer_write = new BufferedWriter(write_file);
            buffer_write.write("\n\n");

            for(int k = 0; k < fmtone_username.size(); k++){
                if(fmtone_code.get(k) == 1 && checkUsername(fmtone_username.get(k), usernames)){
                    buffer_write.write(fmtone_username.get(k)+ " "+
                    fmtone_usertype.get(k)+ " "+fmtone_credit.get(k)+"\n");    
                }
                
            }
            for(int j = 0; j < usernames.size(); j++){
                buffer_write.write(usernames.get(j)+ " "+
                user_type.get(j)+ " "+user_amount.get(j)+"\n");
            
            }
            buffer_write.close();

        } catch(IOException e){
            e.printStackTrace();
        }

	}

    /*Takes in the event title lists, and the seller's username list. Also, uses gettter methods to retrieve the
     number of tickets available and the price of the tickets. Then writes the values from the lists to the Available
     Tickets file replacing the old contents.  */
    public void writeTickets(){
        try{
            File ticketsFile = new File("new_tickets.log");
            if(!ticketsFile.exists()){
                ticketsFile.createNewFile();
            }
            FileWriter write_file = new FileWriter(ticketsFile.getName(), false);
            BufferedWriter buffer_write = new BufferedWriter(write_file);

            tickets = ticketHelper.getTickets();
            for(int k = 0; k < tickets.size(); k++){
                int eventSpace = 25, usernameSpace = 15,
                        countSpace = 3, priceSpace = 6;
                String line = String.format("%" + -eventSpace + "s"
                        + " " + "%" + -usernameSpace + "s"
                        + " " + "%0" + countSpace + "d"
                        + " " + "%0" + priceSpace + ".2f",
                        tickets.get(k).eventName, tickets.get(k).sellerUsername,
                        tickets.get(k).ticketCount, tickets.get(k).ticketPrice);
                buffer_write.write(line+"\n");
            }
            buffer_write.write("END");
            buffer_write.close();

        } catch(IOException e){
            e.printStackTrace();
        }

    }

    public Boolean checkUsername(String identical_username, List<String> old_usernames){

        for(int i=0; i< old_usernames.size(); i++){
            if(identical_username.equals(old_usernames.get(i))){
                return false;
            }
        }
        return true;
    }

	public static void main(String[] args){

        UpdateUserAccounts updateUsersHelper = new UpdateUserAccounts();

        // process tickets file as mergedTransactionFile is parsed
        // TODO: update tickets

        // write updated tickets to tickets.log
        updateUsersHelper.writeTickets();

    /*
		ProcessCurrentUsers current_users = new ProcessCurrentUsers();
		
    */ //used for testing methods and classes
        
        UpdateUserAccounts U = new UpdateUserAccounts();
        U.dailyTransactionParse();

        /* */
        //Tests the ProcessCurrentUsers class
        ProcessCurrentUsers current_users = new ProcessCurrentUsers();
        current_users.readUserAccounts();
        List<String> usernames =  current_users.getUsernameList();
        List<String> user_type = current_users.getUserType();
        List<Double> user_amount = current_users.getUserAmount();
        
        for (int i = 0; i < usernames.size(); i++){
            String usr = usernames.get(i);
            String type = user_type.get(i);
            Double amount = user_amount.get(i);
            System.out.println(usr+user_type+user_amount);
        } 

        U.writeUsers();

	}
}

