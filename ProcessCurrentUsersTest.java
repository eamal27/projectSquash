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

    	currentUsers.parseAccounts("zero_line.txt");
      	currentUsers.parseAccounts("one_line.txt");
       	currentUsers.parseAccounts("two_line.txt");
      	currentUsers.parseAccounts("many_line.txt");


    }

    @Test
    public void testGetAccounts() throws Exception {

    }
}

