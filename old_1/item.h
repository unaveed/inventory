#ifndef ITEM_H
#define ITEM_H
#include <string>

namespace inventory {
	class item {
	private:
		std::string upc;
		std::string name;
		int shelfLife;
		int quantity;
	public:
		item(const std::string upc, const std::string name, int shelfLife, int quantity);
	//	item(const item & other); // Do we need a copy constructor?
		int get_quantity() const;
		std::string get_name(); //necessary?
		int get_shelf_life();
		void remove_life();
	};
}

#endif
