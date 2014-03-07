#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <boost>
#include <map>
#include <vector>

class warehouse {
private:
	std::string name;
    std::map<std::string expDate, list<items> >;
	std::map<std::string, int quant> inventory;
	std::vector<items> foodItems;
	boost::gregorian::date d;
		
public:
	warehouse();	// Default constructor
	warehouse(const std::string location, std::string startDate);	// Constructor
	warehouse(const warehouse & other);		// ???
	~warehouse();

	void receive(std::string upc, int quantity);
	void request(std::string upc, int quantity);	
	void check_expiration();
	void next_day();
};

#endif
