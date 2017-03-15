
public class ErrorLogs{
	
	public String error_type;
	public String error_description;

	public ErrorLogs(){

	}

	public static String determineErrorMessage(String error_type){

		return "ERROR<msg>";
	}

	public static boolean passTicketConstraint(int numTickets){
		boolean pass = true;

		return pass;
	}

	public static boolean passUserConstraint(String username){
		boolean pass = true;

		return pass;

	}
}