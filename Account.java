/**
 * Created by eamal27 on 2017-03-16.
 */
public class Account {
    public String accountType;
    public float creditAmount;
    public String username;
    public boolean deleted;

    public Account(String accountType, float creditAmount, String username) {
        this.accountType = accountType;
        this.creditAmount = creditAmount;
        this.username = username;
        this.deleted = false;
    }

    public float getCreditAmount(){
        return creditAmount;
    }

    public String getUsername(){
        return username;
    }

    public String getAccountType(){
        return accountType;
    }

    public boolean getDeleted(){
        return deleted;
    }
}
