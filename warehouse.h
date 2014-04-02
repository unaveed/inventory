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
 std::string name;
 std::map<std::string, int> inventory;// UPC to amt. of goods
 std::vector<item> foodItems;
 std::map<std::string, int> transactions;
 std::string currentDate;

public:
 warehouse(const std::string location); // Constructor
 ~warehouse();
 void add_item(item food);
 void add_transactions(int num);
 void receive(std::string upc, int shelfLife, int quantity);
 void request(std::string upc, int quantity);
 void next_day();
 std::string get_busiest_day();
 bool in_stock(std::string);
 void set_date(const std::string);
//================FOR DEBUGGING
 int get_num(std::string upc);
 };
}

#endif
