#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "warehouse.h"
#include "item.h"
#include "date.h"
#include "data_helper.h"

using namespace std;

int main  (int argc, char* argv[]) {
	if(argc == 2) {
		inventory::data_helper * helper = new inventory::data_helper();	
	
		string line;
		string city;
		string startDate;
		
		ifstream infile(argv[1]);
		while(getline(infile, line)){
			istringstream is(line);

			if(line[line.size() -1] == '\r')
				line.erase(line.size() - 1);
			
			// Checks the line to see if food item is here.
			if(line.substr(0,8) == "FoodItem"){
				// PLACE HOLDER FOR UPC->Food method
				cout << "Food item found" << endl;
				helper->add_items(line);
			}
			if(line.substr(0,5) == "Start"){
				// PLACE HOLDER FOR CREATING START DATE
				cout << "Create start date" << endl;
				helper->add_date(line);
				helper->get_startdate();
			}
			if(line.substr(0,9) == "Warehouse"){
				// PLACE HOLDER FOR THE WAREHOUSE METHOD
				cout << "Warehouse found" << endl;
				helper->add_warehouse(line);
			}
			if(line.substr(0,8) == "Next day"){
				// PLACE HOLDER FOR CALLING NEXT_DAY METHOD
				cout << "next_day() called here" << endl;
				helper->next_day();
			}
			if(line.substr(0, 7) == "Request"){
				// PLACE HOLDER FOR CALLING REQUESTS
				cout << "request() called here" << endl;
				helper->add_request(line.substr(9));
			}
			if(line.substr(0,7) == "Receive"){
				// PLACE HOLDER FOR CALLING RECEIVES
				cout << "receive() called here" << endl;
				helper->add_receive(line.substr(9));
			}
			if(line.substr(0,3) == "End"){
				// PLACE HOLDER FOR ENDING PROGRAM AND GENERATING REPORT
				cout << "Report by Umair Naveed and Celleste Hollenbeck" << endl;
				helper->unstocked_products();
				helper->fully_stocked_products();
				helper->get_busiest_days();
			}
			cout << line << endl;
		}
	}
	else {
		fprintf(stderr, "Please provide a data file to be read from.\n");
	}
	return 0;
}
