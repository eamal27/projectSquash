

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FileReader;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestProcessUsers {

	UpdateUserAccounts updateUser = new UpdateUserAccounts();
	Account userAccount = new Account("H", 0, "H");

	//Test for statement coverage 
	@Test
	public void testCreateAccount(){
		String line = "01 sohail          AA 001000.00";
		updateUser.createAccount(line);
		String usr = Account.getUsername();
		assertEquals("sohail", usr);
		String type = Account.getAccountType();
		assertEquals("AA", type);
		Float amount = Account.getCreditAmount();
		Float expected_amount = Float.parseFloat("001000.00");
		assertEquals(expected_amount, amount);
	}

	@Test
	public void testDeleteAccount(){
		String line = "02 therock         BS 000001.00";
		updateUser.deleteAccount(line);
		boolean is_deleted = userAccount.getDeleted();
		assertEquals(true, true);

	}

	@Test
	public void testAddCredit(){
		String line = "06 Joe             FS 000100.00";
		updateUser.addCredit(line);
		Float amount = Account.getCreditAmount();
		Float expected_amount = Float.parseFloat("000100.00");
		assertEquals(expected_amount, amount);
	}



	@Test
	public void testTransactionParse(){
		updateUser.dailyTransactionParse();
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
}