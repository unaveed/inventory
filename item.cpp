/**
 * Authors: Celeste Hollenbeck and Umair Naveed
 *
 */

#include "item.h"
#include <iostream>

using namespace std;

namespace inventory
{

	/* Constructor. Just initialize item's variables to those passed in */
	item::item(const string i_upc, int i_shelfLife, int i_q)
	{
	  this->upc = i_upc;
	  this->shelfLife = i_shelfLife;
	  const string tester = "01-23-2015";
	  date d(tester);
	  this->quantity = i_q;
	 } 

	/* Destructor 
	item::~item()
	{
	  //  delete stuff!
	} */
	
	std::string item::get_upc() const {
		return upc; 	
	}
	
	 /* return the number of items with this exp date */
	int item::get_quantity() const
	{
	  return quantity;
	}

	void item::set_quantity(int amount){
		quantity = amount;
	}

	 /* We may not need this?
	string item::get_name()
	{
	  return name;
	  } */

	  /* We may not need this either? 
	string item::get_expiration_date() const
	{
	  return expirationDate;
	  } */

	void item::decrement_shelf_life()
	{
	  --shelfLife;
	}

	int item::get_shelf_life()
	{
	  return shelfLife;
	}
}


