#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <map>
#include <vector>
#include <list>
#include <string>

namespace inventory {
	class date;
	class item;
	class warehouse {
	private:
		std::string name;
		std::map<std::string, std::list<item> > quants; // UPCs to items?
		// Represents the amount of inventory the warehouse has for a particular UPC
		std::map<std::string, int> inventory;// UPC to amt. of goods
		std::vector<item> foodItems;
		// Represents the amount of transactions that have occured,gropued by date
		std::map<std::string, int> transactions;
		// The current date for the warehouse
		std::string currentDate;

	public:
		warehouse(std::string, const std::string); // Constructor
		warehouse(const warehouse & other);
		//~warehouse();
		void receive(std::string upc, int quantity);
		void request(std::string upc, int quantity);
		void add_transactions(int num);
		// void check_expiration(); // We don't need this; next_day does it
		void next_day();
		std::string get_date();

		std::string make_date();
		std::string busiest_day();
		// The following mthods are for TESTING ONLY 
		// -------- DELETE THESE BEFORE HAND IN -----------
		int get_num(std::string);
		int get_trans(std::string);
	};
}
#endif
