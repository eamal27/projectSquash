import junit.framework.TestCase;
import org.junit.Test;

public class AccountTest extends TestCase {
    //admin           AA 003673.47
    String expected_accountType = "AA";
    float expected_creditAmount = 3673.47f;
    String expected_username = "admin";
    Account usrAccount = new Account(expected_accountType, expected_creditAmount, expected_username);

    @Test
    public void testGetCreditAmount() throws Exception {
        float actual_amount = usrAccount.getCreditAmount();

        assertEquals(expected_creditAmount, actual_amount);
    }

    @Test
    public void testGetUsername() throws Exception {
        String actual_username = usrAccount.getUsername();
        assertEquals(expected_username, actual_username);
    }

    @Test
    public void testGetAccountType() throws Exception {
        String actual_accountType = usrAccount.getAccountType();         
        assertEquals(actual_accountType, expected_accountType);
    }

    @Test
    public void testGetDeleted() throws Exception {
        Boolean expected_deleted = false;
        Boolean actual_deleted = usrAccount.getDeleted();

        assertEquals(expected_deleted, actual_deleted);
    }

}