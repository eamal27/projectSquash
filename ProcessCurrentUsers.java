import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.*;

/*ProcessCurrentUsers
This is utilized to retrieve information relating to the 
current users file. The username, user type, and available credit
of the user will be retrived and stored here.  This class reads the 
Current User Accounts file and the DailyTransaction file. Any newly 
created user from the Daily Transactions and the old users from the
current user accounts file will store in separate arraylists.  
 */

public class ProcessCurrentUsers {
	

	public String filename = "CurrentUserAccounts.txt";
	List<String>store_username = new ArrayList<String>();
	List<String>store_user_type = new ArrayList<String>();
	List<Double>store_user_amount = new ArrayList<Double>();

	//Constructor
	public ProcessCurrentUsers(){

	}

	public void setUsername(String username){

		store_username.add(username);
	}

	/*Extracts usernames from the current user accounts file and stores 
	it in arraylist store_users*/
	public List<String> getUsernameList(){
		
		return store_username;
	}

	public void setUserType(String user_type){

		store_user_type.add(user_type);
	}

	public List<String> getUserType(){
		return store_user_type;
	}

	public void setUserAmount(double user_amount){

		store_user_amount.add(user_amount);
	}

	public List<Double> getUserAmount(){
		return store_user_amount;
	}

	public void readUserAccounts(){
		BufferedReader buffer = null;
		try{
			buffer = new BufferedReader(new FileReader(filename));
			String line;
			List<String> new_users = new ArrayList<String>();

			while ((line = buffer.readLine()) != null){
				
				String curr_username = line.substring(0, 15);
				setUsername(curr_username);
				String curr_user_type = line.substring(16, 18);
				setUserType(curr_user_type);
				String curr_user_amount = line.substring(19, 28);
				double user_amount = Double.parseDouble(curr_user_amount);
				setUserAmount(user_amount); 

				//System.out.println(curr_user_type); //Tests that curr_username is storing
													//substring correctly into store_user_type
			}
		} catch(IOException e){
			e.printStackTrace();
		} 
		 finally{
			try{
				if(buffer != null){
					buffer.close();
				}

			} catch (IOException ex){
				ex.printStackTrace();
			}		

		}


	}



	/*Takes in the username of user then searches for the user type 
	for that user. The function parses the user accounts file extracts
	the specific part that gives the user type of the user when the first 
	part of the substring equals the username.
	*/
	public String findUserType(String username){
		
		return "Not found";
	}

	/*Takes in the username of user then searches the available amount of 
	credit for that user. The function parses the user accounts file line by
	line, when the first part of line equals the username then extracts 
	second substring for the user amount.*/
	public double findUserAmount(String username){
			

		return -1.0; 
	}	

}