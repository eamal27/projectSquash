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


	//Constructor
	public ProcessCurrentUsers(){

	}

	/*Extracts usernames from the current user accounts file and stores 
	it in arraylist store_users*/
	public List<String> getUsernameList(){
		BufferedReader buffer = null;
		List<String>store_users = new ArrayList<String>();
		String line; 

		try{
			buffer = new BufferedReader(new FileReader(filename));
			

			while ((line = buffer.readLine()) != null){
				String curr_username = line.substring(0, 15);//extracts the spaces
															// reserved for username
				store_users.add(curr_username); 
				//System.out.println(curr_username); Tests that curr_username is storing
				//substring correctly into store_users

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


		return store_users;
	}

	/*Takes in the username of user then searches for the user type 
	for that user. The function parses the user accounts file extracts
	the specific part that gives the user type of the user when the first 
	part of the substring equals the username.
	*/
	public String findUserType(String username){
		
		BufferedReader buffer = null;
		List<String>store_user_type = new ArrayList<String>();
		String line; 

		try{
			buffer = new BufferedReader(new FileReader(filename));
			
			while ((line = buffer.readLine()) != null){
				String curr_user_type = line.substring(16, 18);
				store_user_type.add(curr_user_type); 
				System.out.println(curr_user_type); //Tests that curr_username is storing
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