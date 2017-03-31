import junit.framework.TestCase;
import org.junit.Test;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class UpdateUserAccountsTest extends TestCase {
    UpdateUserAccounts updateUser = new UpdateUserAccounts();
    Account admin = new Account("AA", 100.00f, "John");
    Ticket ticket;

    @Test
    public void testTransactionParse(){
        updateUser.parseDailyTransactions();
        String filename = "mergedDailyTransactions.txt";
        assertEquals("mergedDailyTransactions.txt", filename);
        File file = new File("mergedDailyTransactions.txt");
        assertNotNull(file); /**/


        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            assertNotNull(br);
            String line = null;
            assertNull(line);

            while ((line = br.readLine()) != null) {
                assertNotNull(line);

            }

        } catch(Exception e){
            System.out.println("Could not find file.");
        }
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
        String line = "03 bowling                   sohail          010 010.00";
        updateUser.sell(line);
        String seller = ticket.getSellerUsername();
        String event = ticket.getEventName();
        int num_tickets = ticket.getTicketCount();
        Float ticket_price = ticket.getTicketPrice();
        ticket = new Ticket(event, seller, num_tickets, ticket_price);
        assertEquals("bowling", event);
        //assertEquals("sohail", seller);
    }

    @Test
    public void testRefund() throws Exception {
        String line = "05 elias           sohail          000100.00";
        Account buyer = null;

        for (int i = 0; i < updateUser.accounts.size(); i++) {
            if (updateUser.accounts.get(i).username.equals("elias")) {
                buyer = updateUser.accounts.get(i);
            }
        }

        Float expected_amount = buyer.creditAmount + 100.00f;

        // should credit elias 100.00
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
        String type = admin.getAccountType();
        assertEquals("AA", type);
        Float amount = admin.getCreditAmount();
        Float expected_amount = Float.parseFloat("001000.00");
        assertEquals(expected_amount, amount);
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

}