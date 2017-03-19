import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.*;

/*Merges changes that occured in the DailyTransaction file with the AvailableTickets file and the CurrentUserAccounts
file. The main method passes the required lists to the methods. Each method  */
class UpdateUserAccounts{

    int transactionCode;
    float creditAmount;
    int numTickets;
    float priceTicket;
    String userType;
    String buyerUsername;
    String sellerUsername;
    String eventName;

	public UpdateUserAccounts(){

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
                            parseFormat1(line);
                            //createAccount();
                            break;
                        case 2:
                            parseFormat1(line);
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
                            parseFormat1(line);
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


    private void parseFormat1(String line) {
        buyerUsername = line.substring(3,18).trim();
        userType = line.substring(19,21).trim();
        creditAmount = Float.parseFloat(line.substring(22,31).trim());
        System.out.println(transactionCode + " " + buyerUsername + " " + userType + " " + creditAmount);
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
		//credit_amount_list.add(new_amount);
	}

	/*Uses the number of tickets list from the Available Tickets file and the list of left over available tickets
	  from the DailyTransaction file. It creates a new list after adding or substracting from the old available
	  tickets list. The event_index will be used to idenitify the correct event to event.*/
	public void updateNumberTickets(ArrayList<Integer> old_number_tickets, List<Integer> change_number_tickets, int event_index){

	}

	/*Takes in the username_list, and gets the stored new credit amount_list then writes to the Current Accounts file
	replacing the old contents */
	public void writeUsers(ArrayList<String> username_list){

	}

	/*Takes in the event title lists, and the seller's username list. Also, uses gettter methods to retrieve the
	 number of tickets available and the price of the tickets. Then writes the values from the lists to the Available
	 Tickets file replacing the old contents.  */
	public void writeTickets(List<String> event_title){

	}

	public static void main(String[] args){
    /*
		ProcessCurrentUsers current_users = new ProcessCurrentUsers();
		List<String>old_users_list = current_users.getUsernameList();
		//System.out.println(old_users_list.get(1)); Used of testing purposes
		String user_type = current_users.findUserType(old_users_list.get(1));
    */ //used for testing methods and classes
        
        UpdateUserAccounts U = new UpdateUserAccounts();
        U.dailyTransactionParse();
	}
}
