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
#include "boost/date_time/gregorian/gregorian.hpp"

/** Constructor: The parameter assigns 
  * a name to the warehouse and it's
  * inventory is initially set to 0.
  */
warehouse (const std::string location, std::string startDate){
	this->name = location;
	this->d = boost::gregorian::date d(boost::gregorian::from_us_string(startDate);
}

// Do we need a destructor? 
warehouse::~warehouse(){
	
}

/** Helper method to add inventory to the warehouse
  * along with an expiration date
  */
void warehouse::add(std::string upc, int quantity){
	
}

/** Takes in a receive request for incoming items.
  * Adds the items to the inventory.
  */
void receive(std::string upc, int quantity){
	// Add item objects to the inventory
}

/** Takes in a request to send out items.Removes
  * the items from the inventory.
  */
void request(std::string upc, int quantity){
	// Search for items in the inventory matching
	// the UPC
		// For matches, remove n number of matches
			// Cases
				// n > than inventory
				// n < than inventory
}

/** Increments the date on all items in inventory
  * and removes expired items from the warehouse
  * inventory.
  */
void next_day(){
	// Increment the day by one
	d += boost::gregorian::days(1);

	// Loop through the inventory and
	// check if there are any expired items
		
		// Remove any expired items

	//Done
}

