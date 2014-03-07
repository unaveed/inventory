/********
* Author: Umair Naveed and Celeste Hollenbeck  
*
********/
#include "warehouse.h"
#include "item.h"
#include "date.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>

namespace inventory {
	/** Constructor: The parameter assigns
	 * a name to the warehouse and it's
	 * inventory is initially set to 0.
	 */
	warehouse::warehouse (std::string location, const std::string startDate){
		this->name = location;
		this->currentDate = startDate;
	}

	warehouse::warehouse (const warehouse & other){
		this->name = "";
		this->currentDate = "";
		
		*this = other;
	}
	  /* Do we need a destructor?
	warehouse::~warehouse(){
	} */


	/** Takes in a receive request for incoming items.
	 * Adds the items to the inventory. Updates the 
	 * transaction count for the day.
	 */
	void warehouse::receive(std::string upc, int quantity){
		// Increase the amount of transactions for the day
		warehouse::add_transactions(quantity);

		// Add item objects to the inventory
		int current = inventory[upc];

		// Prevent negative numbers from being added to the inventory
		int result = current + quantity;
		if (result < 0)
			result = 0;
		inventory[upc] = result;
	}


	/** Takes in a request to send out items.Removes
	 * the items from the inventory. Updates the 
	 * transaction count for the day.
	 */
	void warehouse::request(std::string upc, int quantity){
		// Remove n number of items from the inventory
		warehouse::add_transactions(quantity);
		
		int current = inventory[upc];
		int result = current - quantity; 
		
		inventory[upc] = result;
	}

	/** Adds transactions numbers by UPC to the  
	  * transactions hash_map. Assists in keeping
	  * track of what the busiest day was. 
	  */
	void warehouse::add_transactions(int num){
		int trans = transactions[currentDate];
		int result = num + trans;
		transactions[currentDate] = result;
	}

	/** Increments the date on all items in inventory
	 * and removes expired items from the warehouse
	 * inventory.
	 */
	void warehouse::next_day(){
		// Increment the day by one
		//date d(currentDate);
		//d.add_day();

		// Loop through the inventory and
		// check if there are any expired items

		// Remove any expired items

		//Done
	}

	int warehouse::get_num(std::string upc){	
		int result = inventory[upc];
		return result;
	}

	// Get busiest day
	std::string warehouse::get_busiest_day(){
		typedef std::map<std::string, int>::iterator it_type;

		// Holds the last value
		int last = 0;

		// Holds UPC for the busiest day
		string result;

		// Checks two values of the hashmap against eachother 
		for(it_type iterator = m.begin(); iterator != m.end(); iterator++){
			int compare = iterator->second;
			if(compare > last){
				result = iterator->first;
				last = iterator->second;
			}
		}
		return result;
	}
}
