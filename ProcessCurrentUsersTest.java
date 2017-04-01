import junit.framework.TestCase;
import org.junit.Test;
import java.util.*;
/**
 * Created by eamal27 on 2017-03-30.
 */
public class ProcessCurrentUsersTest extends TestCase {

	String users_file = "CurrentUserAccounts.txt";
	ProcessCurrentUsers currentUsers = new ProcessCurrentUsers();
	Account userAccount = new Account("AA", 21f, "Bob"); ;

    @Test
    public void testParseAccounts() throws Exception {

    	//branch coverage, if != END
    	currentUsers.parseAccounts("TestTextFiles/end_line.txt");
    	String end_user = userAccount.getUsername();
    	assertEquals("Bob", end_user);

    	    	//loop coverag, while loop in parseAccounts
    	currentUsers.parseAccounts("TestTextFiles/blank_line.txt");
    	String no_user = userAccount.getUsername();
    	assertEquals("Bob", no_user);/*should be bob because did not enter loop,
    								 file had null content*/

      	currentUsers.parseAccounts("TestTextFiles/one_line.txt");
      	String user = userAccount.getUsername();
      	assertEquals("Joe", user);
       	
       	currentUsers.parseAccounts("TestTextFiles/two_line.txt");
       	String two_user = userAccount.getUsername();
       	assertEquals("Jack", two_user);//expected user is last username in file

      	currentUsers.parseAccounts("TestTextFiles/many_line.txt");
      	String many_user = userAccount.getUsername();
      	assertEquals("Best Buy", many_user);//expected user is last username in file


    }

    @Test
    public void testGetAccounts() throws Exception {
      	currentUsers.parseAccounts("TestTextFiles/one_line.txt");
    	ArrayList<Account> accountUsers = currentUsers.getAccounts();
    	assertNotNull(accountUsers);
    }

}

