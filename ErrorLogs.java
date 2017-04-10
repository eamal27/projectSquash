

/*
Outputs the error in specific format ERROR:<msg>. This is based
based on what type of error occurred. Error type is sent to this
class from the class that the error occurred in. Constraint messages
give the description and type of error. Fator errors give the the
user the filename affected, the description, and the file.
*/

public class ErrorLogs{

	public String error_type;
	public String error_description;

	public ErrorLogs(String error_type, String file_error){
		this.error_type = error_type;
		this.error_description = error_description;
	}


	//takes in a type of the error, given by each class, whether it is fatal
	 //or contraint error, 

	public static String determineErrorMessage(String error_type){
		String mesg = "":
		if(error_type == "IOException"){
				mesg = error_type+": file not found";
		}
		return "ERROR<msg>";
	}


	//Determines whether the number of tickets is not negative. If negative
	//returns false or else returns true;

	public static boolean passTicketConstraint(int numTickets){
		boolean pass = true;

		return pass;
	}


	/*Determines whether new user created in Daily Transaction file is not a already
	current existing user. Takes in the username and compares with Daily Transaction
	file and the Current User Accounts file. Returns true if users created is unique
	and different from Current User Accounts file.*/

	public static boolean passUserConstraint(String username){
		boolean pass = true;

		return pass;

	}
}
