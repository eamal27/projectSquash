
class Transaction{
	
	bool user_deleted;
	bool admin_nonadmin;

	public:
		std::string create(std::string username, std::string user_type);
		bool isAdmin(std::string);
		void addcreadit(std::string username, float credit_amount);
		void refund(std::string buyer_username, std::string seller_username, float credit_transfer);
		void buy(std::string eventTitle, int quantity, std::string seller_username);
		void sell(std::string eventTitle, float sale_price, int quantity);
		bool deleteUser(std::string username);
		bool isUserDeleted();

};