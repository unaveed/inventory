/** Author: Umair Naveed and Celeste Hollenbeck
  *
  */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "date.h"

namespace inventory
{
class date;

class item {

public:
  item(const std::string upc, int shelfLife, int quantity);
    /*~item(); // Destructor */

  std::string get_expiration_date() const;
  std::string get_upc() const;
  int get_quantity() const;
  int get_shelf_life();
  void set_quantity(int);
  void decrement_shelf_life();

  // std::string get_name(); //necessary? 

private:
   std::string upc;
   std::string name;
   // int shelfLife;
   int shelfLife;
   int quantity;
};
}

#endif
