
#include <iostream>
#include <string>
#include "Transaction.h"

using namespace std;

		bool user_deleted;
		bool admin_nonadmin;
	

		std::string create(std::string username, std::string user_type){

		}
		
		//Returns whether the user type is amdin or not. Uses parameter user_type find out if
		//it is a an admin user.
		bool isAdmin(std::string user_type){
			
			if(user_type == "admin"){//checks for an admin user type
				admin_nonadmin = true; //is an admin
			}
			else{
				admin_nonadmin = false; //is not an admin
			}
		}
		
		void addcreadit(std::string username, float credit_amount){


		}
		
		void refund(std::string buyer_username, std::string seller_username, float credit_transfer){

		}
		
		void buy(std::string eventTitle, int quantity, string seller_username){

		}
		
		void sell(std::string eventTitle, float sale_price, int quantity){

		}
		
		string deleteUser(std::string username){
			user_deleted = true;
			string deleteMsg = "User deleted successfully";

			return deleteMsg;
		}
		
		bool isUserDeleted(){
	
			return user_deleted;
		}