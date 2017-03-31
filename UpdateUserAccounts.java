
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FileReader;
import java.util.*;
import java.io.IOException;
import junit.framework.TestCase;
import static org.junit.Assert.*;
import org.junit.Test;

/*Merges changes that occured in the DailyTransaction file with the AvailableTickets file and the CurrentUserAccounts
file. The main method passes the required lists to the methods. Each method  */
public class UpdateUserAccounts {

    static final float MAX_CREDIT_AMOUNT = 999999.00f;

    ProcessCurrentUsers accountHelper = new ProcessCurrentUsers();
    ArrayList<Account> accounts = null;

    ProcessAvailableTickets ticketHelper = new ProcessAvailableTickets();
    ArrayList<Ticket> tickets = null;
    private float decrementFromBuyer;

    public UpdateUserAccounts(){
        // parse old tickets file and store ticket data
        ticketHelper.ParseTickets();
        tickets = ticketHelper.getTickets();
        accountHelper.parseAccounts();
        accounts =  accountHelper.getAccounts();
	}
    
/* dummy tests */
//	public void testOne() {
//			assertTrue(true);
//	}
//	public void testTwo() {
//			assertTrue(true);
//	}
//	public void testThree() {
//			assertTrue(true);
//	}
//	public void testFour() {
//			assertTrue(true);
//	}
    
	/**
	 *  Parses daily transaction file and populates the username_list and user_credit_list arrays
	 */
		// parse merge daily transaction file	

     
	public void parseDailyTransactions(){
		// parse merge daily transaction file
        String filename = "mergedDailyTransactions.txt";
        File file = new File(filename);
        BufferedReader br = null;

		try {
            br = new BufferedReader(new FileReader(file));
			String line;
			while ((line = br.readLine()) != null) {
				if (!line.equals("00")) {
					int transactionCode = Integer.parseInt(line.substring(0,2).trim());//extracts the code for transaction
                    switch (transactionCode) { //parses in different formats based on the transaction code
                        case 0:
                            updateCreditAmount(line);
                            break;
                        case 1:
                            createAccount(line);
                            break;
                        case 2:
                            deleteAccount(line);
                            break;
                        case 3:
                            sell(line);
                            break;
                        case 4:
                            buy(line);
                            break;
                        case 5:
                            refund(line);
                            break;
                        case 6:
                            addCredit(line);
                            break;
                        default:
                            continue;
                    }
				}
			}
		}catch(Exception e){
			System.out.println("Could not find merged file.");
		}
        finally{
            try{
                if(br != null){
                    br.close();
                }
            } catch (IOException ex){
                ex.printStackTrace();
            }
        }
	}

	// upon logout, update user credit amount if necessary
    private void updateCreditAmount(String line) {
        ArrayList<String> strings = parseFormat1(line);
        String username = strings.get(0);
        String userType = strings.get(1);
        float creditAmount = Float.parseFloat(strings.get(2));

        // iterate through accounts array to find account to add credit to
        for(int k = 0; k < accounts.size(); k++) {
            Account buyer = accounts.get(k);
            if (buyer.username.equals(username) && buyer.creditAmount != creditAmount) {
                // verify credit amount to be set is correct
                if (buyer.creditAmount - decrementFromBuyer == creditAmount) {
                    buyer.creditAmount = creditAmount;
                }
            }
        }
    }

    private void buy(String line) {
        ArrayList<String> strings = parseFormat3(line);
        String eventName = strings.get(0);
        String sellerName = strings.get(1);
        int numTickets = Integer.parseInt(strings.get(2));
        float priceTicket = Float.parseFloat(strings.get(3));

        for (int i=0; i < tickets.size(); i++) {
            if (tickets.get(i).eventName.equals(eventName) && tickets.get(i).sellerUsername.equals(sellerName)) {
                // decrement ticket count bought
                if (tickets.get(i).ticketCount - numTickets >= 0) {
                    tickets.get(i).ticketCount -= numTickets;
                } else {
                    return;
                    // Error: failed to buy (not enough tickets available)
                }
                // find seller and increment credit amount
                for (int a=0; a < accounts.size(); a++) {
                    Account seller = accounts.get(a);
                    if (seller.username.equals(sellerName)) {
                        seller.creditAmount += numTickets * priceTicket;
                        if (seller.creditAmount > MAX_CREDIT_AMOUNT) {
                            seller.creditAmount = MAX_CREDIT_AMOUNT;
                        }
                        // store credit to decrement from buyer (use it on logout)
                        decrementFromBuyer = numTickets * priceTicket;
                        return;
                    }
                }
                // Error: failed to find seller and increment credit amount
            }
        }
    }

    private void sell(String line) {
        ArrayList<String> strings = parseFormat3(line);
        String eventName = strings.get(0);
        String sellerName = strings.get(1);
        int numTickets = Integer.parseInt(strings.get(2));
        float priceTicket = Float.parseFloat(strings.get(3));

        tickets.add(new Ticket(eventName,sellerName,numTickets, priceTicket));
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

    public void addCredit(String line) {
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

    public void deleteAccount(String line) {
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

    public void createAccount(String line) {
        ArrayList<String> strings = parseFormat1(line);
        String username = strings.get(0);
        String userType = strings.get(1);
        float creditAmount = Float.parseFloat(strings.get(2));
        // check if username already exists
        for(int k = 0; k < accounts.size(); k++) {
            if (accounts.get(k).username.equals(username)) {
                // Error: username exists
                //System.out.println("username " + username + " exists");
                return;
            }
        }
        accounts.add(new Account(userType,creditAmount,username));
    }


    private ArrayList<String> parseFormat1(String line) {
        ArrayList<String> strArray = new ArrayList<String>();
        if (line.length() != 31) {
            // Error: fatal error
            System.out.println("Error: fatal error");
            System.exit(0);
        } else {
            // buyerUsername
            strArray.add(line.substring(3, 18).trim());
            // userType
            strArray.add(line.substring(19, 21).trim());
            // creditAmount
            strArray.add(line.substring(22, 31).trim());
        }
        return strArray;
    }

    private ArrayList<String> parseFormat2(String line) {
        ArrayList<String> strArray = new ArrayList<String>();
        if (line.length() != 44) {
            // Error: fatal error
            System.exit(0);
        } else {
            //buyerUsername
            strArray.add(line.substring(3,18).trim());
            //sellerUsername
            strArray.add(line.substring(19,34).trim());
            //creditAmount
            strArray.add(line.substring(35,44).trim());
        }
        return strArray;
    }

    private ArrayList<String> parseFormat3(String line) {
        ArrayList<String> strArray = new ArrayList<String>();
        if (line.length() != 55) {
            // Error: fatal error
            System.exit(0);
        } else {
            // eventName
            strArray.add(line.substring(3,28).trim());
            // sellerUsername
            strArray.add(line.substring(29,44).trim());
            // numTickets
            strArray.add(line.substring(45,48).trim());
            // priceTicket
            strArray.add(line.substring(49,55).trim());
        }
        return strArray;
    }

	/* writes the new set of current users to the currentUserAccounts log file
	replacing the old contents */
	public void writeUsers(){
        try{
            File curr_user_accounts = new File("new_CurrentUserAccounts.txt");
            if(!curr_user_accounts.exists()){
                curr_user_accounts.createNewFile();
            }
            FileWriter write_file = new FileWriter(curr_user_accounts.getName(), false);
            BufferedWriter buffer_write = new BufferedWriter(write_file);

            for(int k = 0; k < accounts.size(); k++){
                // if account is not deleted, print to new currentUserAccounts file
                if (!accounts.get(k).deleted) {
                    int usernameSpace = 15, accTypeSpace = 2, creditSpace = 9;
                    String line = String.format("%" + -usernameSpace + "s"
                                    + " " + "%" + -accTypeSpace + "s"
                                    + " " + "%0" + creditSpace + ".2f",
                            accounts.get(k).username, accounts.get(k).accountType,
                            accounts.get(k).creditAmount);
                    buffer_write.write(line + "\n");
                }
            }
            buffer_write.write("END");
            buffer_write.close();

        } catch(IOException e){
            e.printStackTrace();
        }

	}

    /* writes the tickets for sale to the new
     tickets log file replacing the old contents.  */
    public void writeTickets(){
        try{
            File ticketsFile = new File("new_tickets.txt");
            if(!ticketsFile.exists()){
                ticketsFile.createNewFile();
            }
            FileWriter write_file = new FileWriter(ticketsFile.getName(), false);
            BufferedWriter buffer_write = new BufferedWriter(write_file);

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

	public static void main(String[] args){

        UpdateUserAccounts updateUsersHelper = new UpdateUserAccounts();

        // parse mergedTransactionFile and update tickets and accounts file
        updateUsersHelper.parseDailyTransactions();

        // write updated tickets to tickets.txt
        updateUsersHelper.writeTickets();

        // write updated accounts to currentUserAccounts.txt
        updateUsersHelper.writeUsers();
        System.out.println("Write to ticket and user files, completed");

	}
}

