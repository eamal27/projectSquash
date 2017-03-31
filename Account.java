/**
 * Created by eamal27 on 2017-03-16.
 */
public class Account {
    public static String accountType;
    public static float creditAmount;
    public static String username;
    public static boolean deleted;

    public Account(String accountType, float creditAmount, String username) {
        this.accountType = accountType;
        this.creditAmount = creditAmount;
        this.username = username;
        this.deleted = false;
    }

    public static float getCreditAmount(){
        return creditAmount;
    }

    public static String getUsername(){
        return username;
    }

    public static String getAccountType(){
        return accountType;
    }

    public static boolean getDeleted(){
        return deleted;
    }
}
