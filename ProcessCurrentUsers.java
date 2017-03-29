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

	public ArrayList<Account> accounts;

	public String filename = "CurrentUserAccounts.txt";

	//Constructor
	public ProcessCurrentUsers(){

	}

	public void parseAccounts(){
        // initialize array
        this.accounts = new ArrayList<Account>();

		BufferedReader buffer = null;
		try{
			buffer = new BufferedReader(new FileReader(filename));
			String line;

			while ((line = buffer.readLine()) != null){
				if(!line.equals("END")){
					String curr_username = line.substring(0, 15);
					String curr_user_type = line.substring(16, 18);
					String curr_user_amount = line.substring(19, 28);
					float user_amount = Float.parseFloat(curr_user_amount);
					this.accounts.add(new Account(curr_user_type,user_amount,curr_username));
				}			
				
			}
		} catch(IOException e){
			e.printStackTrace();
		} catch(NumberFormatException n){
			n.printStackTrace();
		} catch(IndexOutOfBoundsException i){
			i.printStackTrace();
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

    // return list of accounts
    public ArrayList<Account> getAccounts(){

        return this.accounts;
    }

}