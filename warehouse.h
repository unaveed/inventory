#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <map>
#include <vector>
#include "item.h"
#include <list>

namespace inventory
{

class warehouse {
private:
 std::string name; // Name of the city
 std::string currentDate; 
 std::vector<item> foodItems; // Keeps track of items in inventory and their quantities and shelf life.
 std::map<std::string, int> inventory; // Maps UPC to total number of items
 std::map<std::string, int> transactions; // Maps date to the number of transactions

public:
 warehouse(const std::string location); 
 void add_item(item food);
 void add_transactions(int num);
 std::string get_busiest_day();
 bool in_stock(std::string);
 void next_day();
 void receive(std::string upc, int shelfLife, int quantity);
 void request(std::string upc, int quantity);
 void remove_item_quantity(std::string, int);
 void set_date(const std::string);
//======FOR DEBUGGING, DELETE ONCE FUNCTIONAL ===//
 int get_num(std::string upc);
 std::string get_city();
 };
}

#endif
