import junit.framework.TestCase;
import org.junit.Test;

/**
 * Created by eamal27 on 2017-03-30.
 */
public class ProcessCurrentUsersTest extends TestCase {

	String users_file = "CurrentUserAccounts.txt";
	ProcessCurrentUsers currentUsers = new ProcessCurrentUsers();

    @Test
    public void testParseAccounts() throws Exception {

    		/*buffer = new BufferedReader(new FileReader(users_file));
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
		*/

    }

    @Test
    public void testGetAccounts() throws Exception {

    }
}

