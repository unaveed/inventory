#include "data_helper.h"
#include "item.h"
#include "warehouse.h"
#include "date.h" 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

namespace inventory {
	data_helper::data_helper(){
		
	}
	void data_helper::build_warehouse(std::string input){
		std::istringstream is(input);
		std::string temp;
		std::string name;

		is >> temp;
		is >> temp;
		is >> name;

		std::cout << name << std::endl;
		warehouse * w = new warehouse(name, startDate);
		warehouses[name] = *w;
	}
	void data_helper::build_items(std::string input){
		std::istringstream is(input);

		// Create strings to hold various data that will be
		// entered into the data structures
		std::string temp;
		std::string upc;
		std::string life;
		std::string piece;
		std::string name;
		
		// Counter to help keep track of where the loop in
		// inside the food item string
		int count = 1;
		while(!is.fail()){
			// Found upc, store it in upc
			if(count == 5){
				is >> upc;
//				std::cout << "UPC: " << upc << std::endl;
			}
			// Found shelfLife, store it in life var
			else if(count == 8){
				is >> life;
//				std::cout << "And this is the life: " << life << std::endl;
			}
			// Found the name of the food item
			else if(count > 9){
				is >> piece;
//				std::cout << "Piece: " << piece << std::endl;

				// Add each piece to the name variable and
				// seperate words with spaces
				name.append(piece);
				name.append(" ");
			}
			// If no relevant data is found, skip to the
			// next word
			else{
				is >> temp;
			}
			count++;
		}

		int n = boost::lexical_cast<int>(life);

		// Add data to the data structures
		codeNames[upc] = name;
		shelfLife[upc] = n; 
	
	}
	void data_helper::build_date(std::string input){
		std::istringstream is(input);

		std::string temp;

		int count = 1;
		while(!is.fail()){
			if(count == 3){
				is >> startDate;
			}
			else {
				is >> temp;
			}
			count++;	
		}
	}
	void data_helper::build_request(std::string line){
	/*	std::istringstream is(line);

		std::string upc;
		std::string quant;
		std::string wh;

		is >> upc;
		is >> quant;
		is >> wh;
		
		int n = boost::lexical_cast<int>(quant); */
/*		
		if(!warehouses.contains(wh)){
			warehouse w(wh, startDate);
			warehouses[wh] = w;
		}
		else {
			warehouse w = warehouses[wh];
			w.request(upc, n);
		}
		*/
	}
	void data_helper::build_receive(std::string line){
	/*	std::istringstream is(line);

		std::string upc;
		std::string quant;
		std::string wh;

		is >> upc;
		is >> quant;
		is >> wh;

		int n = boost::lexical_cast<int>(quant);
		

		warehouse w = warehouses[wh];
		w.receive(upc, n);
		item food(upc, shelfLife[upc], n);

		w.add_item(food); */
	}
	void data_helper::set_start(std::string sdate){
		startDate = sdate;
	}
	//------------------ DEBUG METHOD DEFINITIONS --------//
	int data_helper::get_shelflife(std::string upc){
		return shelfLife[upc]; 
	}
	std::string data_helper::get_code(std::string upc){
		return codeNames[upc];
	}
	std::string data_helper::get_startdate(){
		return startDate;
	}
}
