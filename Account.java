/**
 * Created by eamal27 on 2017-03-16.
 */
public class Account {
    String accountType;
    float creditAmount;
    String username;
    boolean deleted;

    public Account(String accountType, float creditAmount, String username) {
        this.accountType = accountType;
        this.creditAmount = creditAmount;
        this.username = username;
        this.deleted = false;
    }
}
