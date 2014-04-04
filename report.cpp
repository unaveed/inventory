#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "warehouse.h"
#include "item.h"
#include "date.h"
#include "data_helper.h"
#include <queue>
#include <string>

using namespace std;

static queue<string> receiveQueue;
static queue<string> requestQueue;
inventory::data_helper * helper;

/* Processes requests so they are completed
 * after all receives.
 */
void requests(){
	while(!requestQueue.empty()){
		string rItem = requestQueue.front();
		requestQueue.pop();
		helper->add_request(rItem);
	}
};

/* Processes receives at the beginning of
 * the day
 */
void receives(){
	while(!receiveQueue.empty()){
		string qItem = receiveQueue.front();
		receiveQueue.pop();
		helper->add_receive(qItem);
	}
}

int main  (int argc, char* argv[]) {
	if(argc == 2) {
		helper = new inventory::data_helper();	
	
		string line;
		
		ifstream infile(argv[1]);

		// Read the file provided in argv[1]
		while(getline(infile, line)){
			istringstream is(line);

			// Remove \r characters at the end of the line
			if(line[line.size() -1] == '\r')
				line.erase(line.size() - 1);
			
			// Checks the line to see if food item and build
			// data structures containing foodItems.
			if(line.substr(0,8) == "FoodItem"){
//				cout << "Food item found" << endl;
				helper->add_items(line);
			}
			// Check for the Start Date and build it
			if(line.substr(0,5) == "Start"){
//				 cout << "Create start date" << endl;
				helper->add_date(line);
				helper->get_startdate();
			}
			// Check for warehouse names and build warehouses
			if(line.substr(0,9) == "Warehouse"){
//				cout << "Warehouse found" << endl;
				helper->add_warehouse(line);
			}
			// Check for Next Day and process next day information
			if(line.substr(0,8) == "Next day"){
//				cout << "next_day() called here" << endl;

				receives();
				requests();

				helper->next_day();
			}

			// Check for requests and call request()
			if(line.substr(0, 7) == "Request"){
//				cout << "request() called here" << endl;

				std::string receiveName = line.substr(9);
				if(!receiveName.empty() && receiveName[receiveName.size() - 1] == '\r')
					requestQueue.push(receiveName);
				requestQueue.push(receiveName);
			}

			// Check for recieves and call receive()
			if(line.substr(0,7) == "Receive"){
//				cout << "receive() called here" << endl;

				std::string requestName = line.substr(9);
				if(!requestName.empty() && requestName[requestName.size() - 1] == '\r')
					requestName.erase(requestName.size() - 1);

				receiveQueue.push(requestName);
			}

			// Check for the end of the file and do final recieves/requests and print out report. 
			if(line.substr(0,3) == "End"){
				
				receives();
				requests();
				
				cout << "Report by Umair Naveed and Celleste Hollenbeck" << endl;
				helper->unstocked_products();
				helper->fully_stocked_products();
				helper->get_busiest_days();
			}
		}
	}

	// If a data file is not provided, display an error
	else 
		fprintf(stderr, "Please provide a data file to be read from.\n");
	
	return 0;
}
