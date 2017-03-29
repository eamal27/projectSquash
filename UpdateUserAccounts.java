
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

    static final float MAX_CREDIT_AMOUNT = 999999.00f;
    int transactionCode;
    float creditAmount;
    int numTickets;
    float priceTicket;
    String userType;
    String buyerUsername;
    String sellerUsername;
    String eventName;

//    List<String> fmtone_username = new ArrayList<String>();
//    List<String> fmtone_usertype = new ArrayList<String>();
//    List<Float> fmtone_credit = new ArrayList<Float>();
//    List<Integer> fmtone_code = new ArrayList<Integer>();

    ProcessCurrentUsers accountHelper = new ProcessCurrentUsers();
    ArrayList<Account> accounts = new ArrayList<Account>();

    ProcessAvailableTickets ticketHelper = new ProcessAvailableTickets();
    ArrayList<Ticket> tickets = new ArrayList<Ticket>();

	public UpdateUserAccounts(){
        // parse old tickets file and store ticket data
        ticketHelper.ParseTickets();
        accountHelper.parseAccounts();
	}
    /* dummy tests */
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
		File file = new File("mergedDailyTransactions.txt");
		try (BufferedReader br = new BufferedReader(new FileReader(file))) {
			String line;
			while ((line = br.readLine()) != null) {
				if (!line.equals("END")) {
					transactionCode = Integer.parseInt(line.substring(0,2).trim());//extracts the code for transaction
                    switch (transactionCode) { //parses in different formats based on the transaction code
                        case 1:
                            //parseFormat1(line);
                            createAccount(line);
                            break;
                        case 2:
                            //parseFormat1(line);
                            deleteAccount(line);
                            break;
                        case 3:
                            parseFormat3(line);
                            //sell(line);
                            break;
                        case 4:
                            parseFormat3(line);
                            //buy(line);
                            break;
                        case 5:
                            //parseFormat2(line);
                            refund(line);
                            break;
                        case 6:
                            //parseFormat1(line);
                            addCredit(line);
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

    private void refund(String line) {
        ArrayList<String> strings = parseFormat2(line);
        String buyerName = strings.get(0);
        String sellerName = strings.get(1);
        float creditAmount = Float.parseFloat(strings.get(2));

        Account seller = null, buyer = null;
        for(int k = 0; k < accounts.size(); k++) {
            // increment buyer credit amount
            if (buyer == null && accounts.get(k).username.equals(buyerName)) {
                buyer = accounts.get(k);
                if (buyer.creditAmount + creditAmount > MAX_CREDIT_AMOUNT) {
                    buyer.creditAmount += creditAmount;
                } else {
                    // Error: failed to process refund
                }
            }
            // decrement seller credit amount
            if (seller == null && accounts.get(k).username.equals(sellerName)) {
                seller = accounts.get(k);
                if (seller.creditAmount - creditAmount < 0) {
                    seller.creditAmount -= creditAmount;
                } else {
                    // Error: failed to process refund
                }
            }
        }
    }

    private void addCredit(String line) {
        ArrayList<String> strings = parseFormat1(line);
        String username = strings.get(0);
        String userType = strings.get(1);
        float creditAmount = Float.parseFloat(strings.get(2));

        // iterate through accounts array to find account to add credit to
        for(int k = 0; k < accounts.size(); k++) {
            if (accounts.get(k).username.equals(username)) {
                // increment credit amount to a maximum of 999999.00
                if (accounts.get(k).creditAmount + creditAmount <= MAX_CREDIT_AMOUNT) {
                    accounts.get(k).creditAmount += creditAmount;
                } else {
                    accounts.get(k).creditAmount = MAX_CREDIT_AMOUNT;
                }
            }
        }
    }

    private void deleteAccount(String line) {
        ArrayList<String> strings = parseFormat1(line);
        String username = strings.get(0);
        for(int k = 0; k < accounts.size(); k++) {
            if (accounts.get(k).username.equals(username)) {
                if (!accounts.get(k).deleted) {
                    accounts.get(k).deleted = true;
                    return;
                } else {
                    // Error: already deleted
                }
            }
        }
        // Error: account not found
    }

    private void createAccount(String line) {
        ArrayList<String> strings = parseFormat1(line);
        String username = strings.get(0);
        String userType = strings.get(1);
        float creditAmount = Float.parseFloat(strings.get(2));
        // check if username already exists
        for(int k = 0; k < accounts.size(); k++) {
            if (accounts.get(k).username.equals(username)) {
                // Error: username exists
                return;
            }
        }
        accounts.add(new Account(userType,creditAmount,username));
    }


    private ArrayList<String> parseFormat1(String line) {
        ArrayList<String> strArray = new ArrayList<String>();
        // buyerUsername
        strArray.add(line.substring(3,18).trim());
        // userType
        strArray.add(line.substring(19,21).trim());
        // creditAmount
        strArray.add(line.substring(22,31).trim());

        return strArray;
    }

    private ArrayList<String> parseFormat2(String line) {
        ArrayList<String> strArray = new ArrayList<String>();
        //buyerUsername
        strArray.add(line.substring(3,18).trim());
        //sellerUsername
        strArray.add(line.substring(19,34).trim());
        //creditAmount
        strArray.add(line.substring(35,44).trim());

        return strArray;
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
        try{
            File curr_user_accounts = new File("new_CurrentUserAccounts.txt");
            if(!curr_user_accounts.exists()){
                curr_user_accounts.createNewFile();
            }
            FileWriter write_file = new FileWriter(curr_user_accounts.getName(), false);
            BufferedWriter buffer_write = new BufferedWriter(write_file);

            accounts = accountHelper.getAccounts();

            for(int k = 0; k < accounts.size(); k++){
                int usernameSpace = 15, accTypeSpace = 2, creditSpace = 9;
                String line = String.format("%" + -usernameSpace + "s"
                        + " " + "%" + -accTypeSpace + "s"
                        + " " + "%0" + creditSpace + ".2f",
                        accounts.get(k).username, accounts.get(k).accountType,
                        accounts.get(k).creditAmount);
                buffer_write.write(line+"\n");
            }
            buffer_write.write("END");
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
            File ticketsFile = new File("new_tickets.txt");
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

        // update tickets and accounts file as mergedTransactionFile is parsed
        // TODO: update tickets

        // write updated tickets to tickets.txt
        updateUsersHelper.writeTickets();

        // write updated accounts to currentUserAccounts.txt
        updateUsersHelper.writeUsers();

    /*
		ProcessCurrentUsers current_users = new ProcessCurrentUsers();
		
    */ //used for testing methods and classes
        
        //UpdateUserAccounts U = new UpdateUserAccounts();
        //U.dailyTransactionParse();

        /* */
        //Tests the ProcessCurrentUsers class
        //ProcessCurrentUsers current_users = new ProcessCurrentUsers();
        //current_users.readUserAccounts();
        //List<String> usernames =  current_users.getUsernameList();
        //List<String> user_type = current_users.getUserType();
        //List<Double> user_amount = current_users.getUserAmount();
        
        //for (int i = 0; i < usernames.size(); i++){
        //    String usr = usernames.get(i);
        //    String type = user_type.get(i);
        //    Double amount = user_amount.get(i);
        //    System.out.println(usr+user_type+user_amount);
        //}

        //U.writeUsers();

	}
}

