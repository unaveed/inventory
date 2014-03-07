/**
 * Celeste Hollenbeck, Umair Naveed
 *
 */
#include "item.h"

using namespace std;

namespace inventory {
	/* Constructor. Just initialize item's variables to those passed in */
	item::item(const string upc, const string name, const int expDate, int quanitity)
	{
	  this->upc = upc;
	  this->name = name;
	  this->expDate = expDate;
	  this->quantity = quantity;
	}


	/* Destructor */
	item::~item()
	{
	  //  delete stuff!
	}


	/* return the number of items with this exp date */
	int item::get_quantity() const
	{
	  return quantity;
	}


	// We may not need this?
	string item::get_name()
	{
	  return name;
	}


	// We may not need this either?
	string item::get_expiration_date()
	{
	  return expDate; 
	}
}
