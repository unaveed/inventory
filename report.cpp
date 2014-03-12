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
		
		ifstream infile(argv[1]);
		cout << "Report by Umair Naveed and Celleste Hollenbeck" << endl;
		cout << "" << endl;	
		while(getline(infile, line)){
			istringstream is(line);
			
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
			}
			if(line.substr(0,9) == "Warehouse"){
				// PLACE HOLDER FOR THE WAREHOUSE METHOD
				cout << "Warehouse found" << endl;
				helper->add_warehouse(line);
			}
			if(line.substr(0,8) == "Next day"){
				// PLACE HOLDER FOR CALLING NEXT_DAY METHOD
				cout << "next_day() called here" << endl;
			}
			if(line.substr(0, 7) == "Request"){
				// PLACE HOLDER FOR CALLING REQUESTS
				cout << "request() called here" << endl;
			}
			if(line.substr(0,7) == "Receive"){
				// PLACE HOLDER FOR CALLING RECEIVES
				cout << "receive() called here" << endl;
			}
			if(line.substr(0,3) == "End"){
				// PLACE HOLDER FOR ENDING PROGRAM AND GENERATING REPORT
				cout << "Generate report here" << endl;
				cout << "Unstocked Products:" << endl;
				cout << "" << endl;
				cout << "Fully-Stocked Products:" << endl;
			}
			cout << line << endl;
		}
	}
	return 0;
}
