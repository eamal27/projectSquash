

class System {

	bool logged_in;
	
	public:
		std::string initialLogin(std::string systemCmd);
		bool verifyUsername(std::string username);
		bool initiateTransaction(std::string user_type, std::string transactin_name);
		std::string logout();


};