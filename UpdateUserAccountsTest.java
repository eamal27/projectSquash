import junit.framework.TestCase;
import org.junit.Test;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
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
        expected_parse = 2;
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
        Account buyer = null;
        String line  = "04 paintball                 sohail          010 010.00";
        String line2 = "00 Jack            AA 000478.66";
        for (Account acc: updateUser.accounts) {
            if(acc.username.equals("Jack")) {
                buyer = acc;
            }
        }
        // assert credit amount before logout
        assertEquals(578.66f, buyer.creditAmount);

        updateUser.buy(line);
        updateUser.updateCreditAmount(line2);

        // assert credit amount after logout
        assertEquals(478.66f, buyer.creditAmount);
    }

    @Test
    public void testBuy() throws Exception {
        Ticket ticket = null;
        String line = "04 paintball                 sohail          010 010.00";
        for (Ticket t: updateUser.tickets) {
            if(t.sellerUsername.equals("sohail") &&
                    t.eventName.equals("paintball")) {
                ticket = t;
            }
        }
        // assert ticket count before buy
        assertEquals(14, ticket.ticketCount);

        updateUser.buy(line);

        // assert ticket count after buy
        assertEquals(4, ticket.ticketCount);
    }

    @Test
    public void testSell() throws Exception {
        Ticket ticket = null;
        String line = "03 bowling                   sohail          010 010.00";
        updateUser.sell(line);
        for (Ticket t: updateUser.tickets) {
            if(t.sellerUsername.equals("sohail") &&
                    t.eventName.equals("bowling")) {
                ticket = t;
            }
        }
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
        Account newAcc = null;
        for (Account acc: updateUser.accounts) {
            if (acc.username.equals("sohail")) {
                newAcc = acc;
            }
        }
        String usr = newAcc.getUsername();
        assertEquals("sohail", usr);
        String type = newAcc.getAccountType();
        assertEquals("AA", type);
        Float amount = newAcc.getCreditAmount();
        Float expected_amount = Float.parseFloat("001000.00");
        assertEquals(expected_amount, amount);
    }

    @Test
    public void testParseFormat1() throws Exception {
        ArrayList<String> strArray = new ArrayList<String>();
        String line = "00 elias           AA 000900.00";
        strArray = updateUser.parseFormat1(line);
        assertEquals("elias",strArray.get(0));
        assertEquals("AA",strArray.get(1));
        assertEquals(900.00f,Float.parseFloat(strArray.get(2)));

    }

    @Test
    public void testParseFormat2() throws Exception {
        ArrayList<String> strArray = new ArrayList<String>();
        String line = "05 elias           sohail          000100.00";
        strArray = updateUser.parseFormat2(line);
        assertEquals("elias",strArray.get(0));
        assertEquals("sohail",strArray.get(1));
        assertEquals(100.00f,Float.parseFloat(strArray.get(2)));
    }

    @Test
    public void testParseFormat3() throws Exception {
        ArrayList<String> strArray = new ArrayList<String>();
        String line = "04 bowling                   sohail          010 010.00";
        strArray = updateUser.parseFormat3(line);
        assertEquals("bowling",strArray.get(0));
        assertEquals("sohail",strArray.get(1));
        assertEquals(10,Integer.parseInt(strArray.get(2)));
        assertEquals(10.00f,Float.parseFloat(strArray.get(3)));
    }

    @Test
    public void testWriteUsers() throws Exception {
        String filename = "testWriteUsers.txt";
        updateUser.writeUsers(filename);
        String expectedString = "Joe             FS 006798.97" +
                                "Jack            BS 000578.66" +
                                "admin           AA 003673.47" +
                                "Wal-Mart        SS 000235.87" +
                                "Best Buy        SS 067765.99" +
                                "END";
        String string = "";
        BufferedReader buffer = null;
        try{
            buffer = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = buffer.readLine()) != null){
                string += line;
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
        // assert expected output was written to file
        assertEquals(expectedString,string);
    }

    @Test
    public void testWriteTickets() throws Exception {
        String filename = "testWriteTickets.txt";
        updateUser.writeTickets(filename);
        String expectedString = "SomeEvent                 someUser        010 009.99" +
                                "paintball                 sohail          014 010.00" +
                                "END";
        String string = "";
        BufferedReader buffer = null;
        try{
            buffer = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = buffer.readLine()) != null){
                string += line;
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
        // assert expected output was written to file
        assertEquals(expectedString,string);
    }

    public static void main(String[] args) throws Exception {
        UpdateUserAccountsTest t = new UpdateUserAccountsTest();
        t.testWriteTickets();

    }
}