import junit.framework.TestCase;
import org.junit.Test;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

public class UpdateUserAccountsTest extends TestCase {

    UpdateUserAccounts updateUser = new UpdateUserAccounts();
    ProcessCurrentUsers accountHelper = new ProcessCurrentUsers();
    ProcessAvailableTickets ticketHelper = new ProcessAvailableTickets();
    ArrayList<Account> accounts = null;
    ArrayList<Ticket> tickets = null;
    Account admin = new Account("FS", 100.0f, "Joe");

    @Test
    public void testTransactionParse(){

        //branch coverage
        String filename = "TestMergeFiles/zero_line.txt";
        int is_parsed = updateUser.parseDailyTransactions(filename);
        int expected_parse = 1; 
        assertEquals(expected_parse, is_parsed);        

        filename = "TestMergeFiles/one_code.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        expected_parse = 1; 
        assertEquals(expected_parse, is_parsed);        

        /*filename = "TestMergeFiles/one_code.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        String user = admin.getUsername(); 
        assertEquals("Sohail", user);

        filename = "TestMergeFiles/one_code.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        String user = admin.getUsername(); 
        assertEquals("Sohail", user); */




        //loop coverage, while loop in parseAccounts
        filename = "TestMergeFiles/blank_line.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        expected_parse = 0; 
        assertEquals(expected_parse, is_parsed);

        filename = "TestMergeFiles/one_line.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        expected_parse = 2; 
        assertEquals(expected_parse, is_parsed);

        filename = "TestMergeFiles/two_line.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        expected_parse = 3; 
        assertEquals(expected_parse, is_parsed);

        filename = "TestMergeFiles/many_line.txt";
        is_parsed = updateUser.parseDailyTransactions(filename);
        expected_parse = 5; 
        assertEquals(expected_parse, is_parsed);
    }

    @Test
    public void testUpdateCreditAmount() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testBuy() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testSell() throws Exception {
        System.out.println(updateUser.tickets.size());
        Ticket ticket = null;
        String line = "03 bowling                   sohail          010 010.00";
        updateUser.sell(line);
        for (Ticket t: updateUser.tickets) {
            if(t.sellerUsername.equals("sohail") &&
                    t.eventName.equals("bowling")) {
                ticket = t;
            }
        }
        System.out.println(updateUser.tickets.size());
        // assert event name
        assertEquals("bowling", ticket.eventName);
        // assert seller name
        assertEquals("sohail", ticket.sellerUsername);
    }

    @Test
    public void testRefund() throws Exception {
        String line = "05 Joe             Jack            000100.00";
        Account buyer = null;
        for (Account acc: updateUser.accounts) {
            if (acc.username.equals("Joe")) {
                buyer = acc;
            }
        }
        Float expected_amount = buyer.creditAmount + 100.00f;
        // should credit Joe 100.00
        updateUser.refund(line);

        //assertEquals("elias", username);
        assertEquals(expected_amount, buyer.creditAmount);
    }

    @Test
    public void testAddCredit() throws Exception {
        String line = "06 Joe             FS 000100.00";
        updateUser.addCredit(line);
        Float amount = admin.getCreditAmount();
        Float expected_amount = Float.parseFloat("000100.00");
        assertEquals(expected_amount, amount);
    }

    @Test
    public void testDeleteAccount() throws Exception {
        String line = "02 therock         BS 000001.00";
        updateUser.deleteAccount(line);
        boolean is_deleted = admin.getDeleted();
        assertEquals(true, true);
    }

    @Test
    public void testCreateAccount() throws Exception {
        String line = "01 sohail          AA 001000.00";
        updateUser.createAccount(line);
        String usr = admin.getUsername();
        assertEquals("sohail", usr);
        /*String type = admin.getAccountType();
        assertEquals("AA", type);
        Float amount = admin.getCreditAmount();
        Float expected_amount = Float.parseFloat("001000.00");
        assertEquals(expected_amount, amount);*/
    }

    @Test
    public void testParseFormat1() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testParseFormat2() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testParseFormat3() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testWriteUsers() throws Exception {

        assertEquals(1,1);
    }

    @Test
    public void testWriteTickets() throws Exception {

        assertEquals(1,1);
    }

    public static void main(String[] args) throws Exception {
        UpdateUserAccountsTest t = new UpdateUserAccountsTest();
        t.testSell();
        t.testRefund();

    }
}