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
        //array should be empty since no users in end_line.txt
    	assertEquals(0, currentUsers.accounts.size());

        //loop coverag, while loop in parseAccounts
    	currentUsers.parseAccounts("TestTextFiles/blank_line.txt");
		//array should be empty since no users in end_line.txt
		assertEquals(0, currentUsers.accounts.size());

      	currentUsers.parseAccounts("TestTextFiles/one_line.txt");
      	String user = currentUsers.accounts.get(0).getUsername();
      	assertEquals("Joe", user);
       	
       	currentUsers.parseAccounts("TestTextFiles/two_line.txt");
		String first_user = currentUsers.accounts.get(0).getUsername();
       	String second_user = currentUsers.accounts.get(1).getUsername();
		assertEquals("Joe", first_user);
       	assertEquals("Jack", second_user);

      	currentUsers.parseAccounts("TestTextFiles/many_line.txt");
		String user1 = currentUsers.accounts.get(0).getUsername();
		String user2 = currentUsers.accounts.get(1).getUsername();
		String user3 = currentUsers.accounts.get(2).getUsername();
		String user4 = currentUsers.accounts.get(3).getUsername();
		String user5 = currentUsers.accounts.get(4).getUsername();
		assertEquals("Joe", user1);
		assertEquals("Jack", user2);
      	assertEquals("admin", user3);
		assertEquals("Wal-Mart", user4);
		assertEquals("Best Buy", user5);

    }

    @Test
    public void testGetAccounts() throws Exception {
      	currentUsers.parseAccounts("TestTextFiles/one_line.txt");
    	ArrayList<Account> accountUsers = currentUsers.getAccounts();
    	assertNotNull(accountUsers);
    }

}

