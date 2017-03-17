import java.util.*;

class UpdateUserAccounts{
	
	public UpdateUserAccounts(){

	}

	public void updateAmount(String username){

	}

	public void updateTickets(String event_title){

	}

	public void writeUsers(ArrayList<String> username_list){

	}

	public static void main(String[] args){

		ProcessCurrentUsers current_users = new ProcessCurrentUsers();
		List<String>old_users_list = current_users.getUsernameList();
		//System.out.println(old_users_list.get(1));
		String user_type = current_users.findUserType(old_users_list.get(1));
	}
}

