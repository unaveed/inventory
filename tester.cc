/** Author: Umair Naveed and Celeste Hollenbeck
  *
  */

#include "warehouse.h"
#include "item.h"
#include "date.h"
#include <map>
#include <iostream>

using namespace std;

int main() {
	inventory::warehouse ware("Cincinati", "10/20/2010");

	string upc = "09234532";
	string upc1 = "2342143";
	string upc2 = "2342123";

	ware.receive(upc, 30);
	cout << "Expecting 30, get: " << ware.get_num(upc) << endl;

	ware.request(upc, 15);
	cout << "Expecting 15, get: " << ware.get_num(upc) << endl;

	ware.next_day();

	ware.receive(upc, 25);
	ware.request(upc, 5);
	ware.next_day();
	
	ware.receive(upc1, 40);
	ware.request(upc1, 21);
	ware.next_day();
	ware.receive(upc2, 45);
	ware.request(upc2, 15);
	ware.next_day();
	
	cout << "Busiest day: " << ware.get_busiest_day() << endl;
	cout << "In stock, should be 1: " << ware.in_stock(upc) << endl;
	cout << "Actual stock: " << ware.get_num(upc) << endl;
	cout << "In stock, should be 1: " << ware.in_stock(upc1) << endl;
	cout << "Actual stock: " << ware.get_num(upc1) << endl;
	cout << "In stock, should be 0: " << ware.in_stock("34536242") << endl;
	cout << "Actual stock: " << ware.in_stock("34536242") << endl; 
}
