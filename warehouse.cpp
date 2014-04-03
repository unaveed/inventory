/********
* Author: Umair Naveed and Celeste Hollenbeck  
*
********/

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "warehouse.h"
#include "item.h"
#include <vector>
#include <list>

namespace inventory
{

	/** Constructor: The parameter assigns
	 * a name to the warehouse and its
	 * inventory is initially set to 0.
	 */ 
	warehouse::warehouse (const std::string location){
		this->name = location;
		this->currentDate = "";
	}

	/**
	 * Takes in a positive number of received or requested products to
	 * tally the total number of daily transactions
	 */
	void warehouse::add_transactions(int num)
	{
	  // retrieve the day's transactions
	  int trans = transactions[currentDate];
	  
	  // add passed-in transactions to total
	  int result = num + trans; 
	
	  // assign new value back into transactions
	  transactions[currentDate] = result; 	
	}

	/** Takes in a receive request for incoming items.
	 * Adds the items to the inventory.
	 */
	void warehouse::receive(std::string upc, int shelfLife, int quantity){
	  //=================Celeste's code -- have a look
	  
	  // add number of received items to transaction tally
	  add_transactions(quantity); 
	 
	  // Create an item and put it into the item vector
	  item *a = new item(upc, shelfLife, quantity);
	  foodItems.push_back(*a);

	  // Uncomment to debug
	  //std::cout << a->get_shelfLife() << std::endl;

	  int current = inventory[upc]; // retrieve current inventory count
	  int result = current + quantity; // add request amount to inventory
	  inventory[upc] = result; // assign the new result back into inventory
	}

	/** Takes in a request to send out items.Removes
	 *  the items from the inventory.
	 */
	void warehouse::request(std::string upc, int quantity){
		// retrieve current inventory count of item
		int current = inventory[upc];

		// Add the amount of items requested to
		// the transaction count
		add_transactions(quantity);
	
		if(current > 0){
			// TODO: Take elements out of foodItems
			remove_item_quantity(upc, quantity);
		}
		
		// Get the amount of inventory left after shipping
		// out items of given upc
		int result = current - quantity;

		// Prevent negative numbers from being stored
		// in the inventory
		if(result < 0)
			result = 0;

		// Store new inventory count
		inventory[upc] = result;
	}

	/** Increments the date on all items in inventory
	 * and removes expired items from the warehouse
	 * inventory.
	 */
	void warehouse::next_day(){
		// Increment the day by one
		{
			date *d = new date(this->currentDate);
			d->add_day();
			this->currentDate = d->get_date();
		}
		
		// Iterator through inventory and 
		// remove expired items.
		for(std::vector<item>::size_type i = 0; i != foodItems.size(); ){
			foodItems[i].decrement_shelf_life();
			
			// Check if the food item at index i is expired	
			if(foodItems[i].get_shelf_life() == 0){
				{
					// Get upc, amount expired, and current amount 
					// from the expired item.
					std::string item_upc = foodItems[i].get_upc();
					int amount = foodItems[i].get_quantity();
					int currentAmount = inventory[item_upc];
			
					currentAmount -= amount;
					
					// Prevent negative quantity from being stored
					// in inventory
					if(currentAmount < 0)
						inventory[item_upc] = 0;
					else
						inventory[item_upc] = currentAmount;
				}	
				foodItems.erase(foodItems.begin()+i);
			}
			// Increment only if food item is not being removed
			else
				i++;
		}
	}

	/* Returns whether an item of a given UPC is
	 * in stock. UPC's that are not in the inventory
	 * are considered out of stock.
	 */
	bool warehouse::in_stock(std::string upc){
		// Check if upc exists in inventory
		if(inventory.count(upc) == 0)
			return false;
		else{
			bool res = inventory[upc] > 0;
			return inventory[upc] > 0;
		}
	}

	/* May not be needed 
	 */
	void warehouse::add_item(item foodItem){
		foodItems.push_back(foodItem);	
	}

	/* Removes n quantities of items from foodItems
	 * matching the upc given by the parameter of the
	 * same name. Items with 0 quantity are removed
	 * from foodItems altogether.
	 */
	void warehouse::remove_item_quantity(std::string upc, int n){
		for(std::vector<item>::iterator it = foodItems.begin(); it != foodItems.end(); ){
			// Check if current foodItem matches the upc
			if(it->get_upc() == upc){
				// Check if there are more items to be shipped
				// than there are in current food item. This
				// item will be removed from foodItems
				if(n > it->get_quantity()){
					n -= it->get_quantity();
					it = foodItems.erase(it);
				}
				else {
					int quantity = it->get_quantity();
					quantity -= n;
					n = 0;
					it->set_quantity(quantity);
					break;
				}
			}
			else 
				++it;
		}
	}

	/** Checks the inventory to see which day had the
	  * most combined requests and receives. Returns the
      * warehouse name, date, and number of transactions
	  * that fulfill this requirement. In the case of
	  * ties, the newer date is returned.
	  */
	std::string warehouse::get_busiest_day(){
		// Holds the last value
		int last = 0;

		// Holds the day with the most transactions
		std::string day = currentDate;

		// Holds Warehouse name, date, and transaction amount
		// for the busiest day
		std::string result = name;

		// Checks two values of the hashmap against eachother
		typedef std::map<std::string, int>::iterator it_type;
		for(it_type iterator = transactions.begin(); iterator != transactions.end(); iterator++){
			int compare = iterator->second;

			// If two dates have the same number of 
			// transactions, the newer dates information
			// is stored in result
			if(compare == last){
				date *currentDateCompare = new date(day);
				date *newDateCompare = new date(iterator->first);

				if(currentDateCompare > newDateCompare)
					day = currentDateCompare->get_date();
				else
					day = newDateCompare->get_date();

				delete currentDateCompare;
				delete newDateCompare;
			}

			// If the current date has more transactions than 
			// the previous date, the pertinent information
			// is stored in result
			if(compare > last){
				day = iterator->first;
				last = iterator->second;
			}
		}
		
		// Convert transaction number to
		// a string
		std::ostringstream convert;
		convert << last;
	
		// Format the result to the function
		// contract requirements
		result.append(" ");
		result.append(day);
		result.append(" ");
		result.append(convert.str());
		
		return result;
	}

	/* Sets the current date to today's date */
	void warehouse::set_date(const std::string today){
		this->currentDate = today;		
	}

	/**
	 * ======================FOR DEBUGGING
	 */
	int warehouse::get_num(std::string upc)
	{
	  int result = inventory[upc];
	  return result;  
	}
	
}
