#ifndef DATA_HELPER_H
#define DATA_HELPER_H

#include <string>
#include "item.h"
#include "warehouse.h"
#include "date.h"
#include <vector>

namespace inventory {
	class data_helper {
		private:
			// Maps the UPC to the name of the product
			std::map<std::string, std::string> *codeNames;

			// Maps the UPC to the shelf life
			std::map<std::string, int> *shelfLife;

			// Maps warehouses to their names
			std::map<std::string, warehouse*> *warehouses;
			std::string startDate;
		public:
			data_helper();
			void add_warehouse(std::string);
			void add_items(std::string);
			void add_date(std::string);
			void add_request(std::string);
			void add_receive(std::string);
			void set_start(std::string);
			//----------- DEDBUG METHODS BELOW ------------//
			int get_shelflife(std::string upc);
			std::string get_code(std::string upc);
			std::string get_startdate();
	};
}
#endif
