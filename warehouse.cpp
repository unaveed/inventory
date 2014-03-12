/********
* Author: Umair Naveed and Celeste Hollenbeck  
*
********/

#include <iostream>
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
	warehouse::warehouse (const std::string location, std::string startDate){
	this->name = location;
	//this->d = boost::gregorian::from_us_string(startDate);
	this->currentDate = startDate;

	}

	  /* Do we need a destructor?
	warehouse::~warehouse(){
	} */

	/**
	 * Takes in a positive number of received or requested products to
	 * tally the total number of daily transactions
	 */
	void warehouse::add_transactions(int num)
	{
	  //==============We need to convert from a gregorian date to a string!
	  int trans = transactions[currentDate]; // retrieve the day's transactions
	  int result = num + trans; // add passed-in transactions to total
	  transactions[currentDate] = result; // assign new value back into transactions
	}

	/** Takes in a receive request for incoming items.
	 * Adds the items to the inventory.
	 */
	void warehouse::receive(std::string upc, int shelfLife, int quantity){
	  //=================Celeste's code -- have a look
	  add_transactions(quantity); // add number of received items to transaction tally
	 
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
	 * the items from the inventory.
	 */
	void warehouse::request(std::string upc, int quantity){
	  	  
	  int current = inventory[upc]; // retrieve current inventory count of item
	  // Check if more quantity is being requested than is in stock
	  // if this is the case, add to transactions the number that is 
	  // actually in stock
	  if(quantity > current)
	  	add_transactions(current);
	  else
	  	add_transactions(quantity);

	  int result = current - quantity;   // subtract request amt from inventory
	  if(result < 0) // If quantity of item is negative, set it to zero
		result = 0;
	  inventory[upc] = result; // set the inventory value again
	}

	/** Increments the date on all items in inventory
	 * and removes expired items from the warehouse
	 * inventory.
	 */
	void warehouse::next_day(){
	// Increment the day by one
	  date d(currentDate);
	  d.add_day();
	  currentDate = d.get_date();
	}

	/**
	 * ======================FOR DEBUGGING
	 */
	int warehouse::get_num(std::string upc)
	{
	  int result = inventory[upc];
	  return result;  
	}

	/** Checks the inventory to see which day had the
	  * most combined requests and receives. Returns the
      * date the fulfills this requirement. In the case of
	  * ties, the newer date is returned.
	  */
	std::string warehouse::get_busiest_day(){
		typedef std::map<std::string, int>::iterator it_type;

		// Holds the last value
		int last = 0;

		// Holds UPC for the busiest day
		std::string result;

		// Checks two values of the hashmap against eachother
		for(it_type iterator = transactions.begin(); iterator != transactions.end(); iterator++){
			int compare = iterator->second;
			if(compare > last){
				result = iterator -> first;
				last = iterator-> second;
			}
			if(compare == last){
				// Do something

			}
		}

		return result;
	}

	bool warehouse::in_stock(std::string upc){
		int result = inventory[upc];

		return result > 0;
	}

	void warehouse::add_item(item foodItem){
		foodItems.push_back(foodItem);	
	}
	
}