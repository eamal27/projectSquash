import java.util.*;

/*Merges changes that occured in the DailyTransaction file with the AvailableTickets file and the CurrentUserAccounts
file. The main method passes the required lists to the methods. Each method  */
class UpdateUserAccounts{

	public List<Float> credit_amount_list;
	
	public UpdateUserAccounts(){

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
		credit_amount_list.add(new_amount);
	}

	public List<Float> getUserAmount(){
		return credit_amount_list;
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

		ProcessCurrentUsers current_users = new ProcessCurrentUsers();
		List<String>old_users_list = current_users.getUsernameList();
		//System.out.println(old_users_list.get(1)); Used of testing purposes
		String user_type = current_users.findUserType(old_users_list.get(1));
	}
}

