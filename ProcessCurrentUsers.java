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
	
	public ArrayList<String> old_users;
	public ArrayList<String> new_users;
	public String filename;


	public ProcessCurrentUsers(){

	}

	public List<String> compareUsername(){
		BufferedReader buffer = null;
		try{
			buffer = new BufferedReader(new FileReader("OldCurrentUsers.txt"));
			String line;
			List<String> new_users = new ArrayList<String>();
			while ((line = buffer.readLine()) != null){
				String[] curr_usr_info = line.split("\\{2}");//Best Buy row does not split properly
				new_users.add(curr_usr_info[0]); 


			}
			System.out.println(new_users.get(4));
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



		return new_users;
	}

	public String findUserType(String username){
		
		return "Not known";
	}

	public double findUserAmount(String username){
		
		return -1.0; 
	}	

}