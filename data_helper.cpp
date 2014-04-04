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
		this->codeNames;
		this->shelfLife;
		this->warehouses;
		this->startDate;
	}

	/** Parses the data from the text file and adds a warehouse
	  * to the warehouses map. 
	  */
	void data_helper::add_warehouse(std::string input){
		std::string name = input.substr(12);

		if(name[name.size() - 1] == ' ')
			name.erase(name.size() - 1);
		
		warehouse *w = new warehouse(name);
		warehouses.insert(std::pair<std::string, warehouse*> (name, w) );
	}

	/** Parses data from the text file and adds food items 
	  * to the items map
	  */
	void data_helper::add_items(std::string input){
		std::istringstream is(input);

		if(input[input.size() - 1] == ' ')
			input.erase(input.size() - 1);

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
			}
			else if(count == 8){
				is >> life;
			}
			// Found the name of the food item
			else if(count > 9){
				is >> piece;
				
				if(piece != ""){
					// Add each piece to the name variable and
					// seperate words with spaces
					name.append(piece);
					name.append(" ");
				}

				piece = "";
			}
			// If no relevant data is found, skip to the
			// next word
			else{
				is >> temp;
				std::cout << temp << std::endl;
			}
			count++;
		}


		int n = boost::lexical_cast<int>(life);

		// Add data to the data structures
		codeNames.insert(std::pair<std::string, std::string> (upc, name) );
		shelfLife.insert(std::pair<std::string, int> (upc, n) );
		/* shelfLife->operator[](upc) = n; */
	
	}

	/* Parses data from the text file to retrieve start
	 * and store it in the startDate member.
	 */
	void data_helper::add_date(std::string input){
		if(input[input.size() -1] == ' ')
			input.erase(input.size() - 1);

		startDate = input.substr(12);

		// Loop through and set the start date for every warehouse
		typedef std::map<std::string, warehouse*>::iterator it_type;
		for(it_type iterator = warehouses.begin(); iterator != warehouses.end(); iterator++){
			iterator->second->set_date(startDate);	
		}
	}

	/* Calls the next_day function on each warehouse in the
	 * warehouses map.
	 */
	void data_helper::next_day(){
		
		for(std::map<std::string, warehouse*>::iterator it = warehouses.begin(); it != warehouses.end(); ++it){			
			it->second->next_day();	
		}
	}

	/* Parses receive information from the input string
	 * into a UPC, food item quantity, and city name.
	 * The city variable is used to lookup existing warehouses
	 * by calling warehouse functions to update quantities
	 * in inventory.
	 */
	void data_helper::add_request(std::string line){
	//	std::istringstream is(line);

		// Variables to hold the UPC, quantity requested, and name of warehouse
		std::string upc;
		std::string quant;
		std::string city;
/*
		is >> upc;
		is >> quant;
		is >> city;
		
*/
		build_strings(line, upc, quant, city);
		int n = boost::lexical_cast<int>(quant); 
	
		warehouse *w = warehouses[city];
		w->request(upc, n);
		warehouses[city] = w;
	}

	/* Parses receive information from the input string
	 * into a UPC, food item quantity, and city name.
	 * The city variable is used to lookup existing warehouses
	 * by calling warehouse functions to update quantities
	 * in inventory.
	 */
	void data_helper::add_receive(std::string line){
		//std::istringstream is(line);

		std::string upc;
		std::string quant;
		std::string city;
	//	std::string temp;
		
		/*
		is >> upc;
		is >> quant;
		is >> city;

		while(!is.fail()){
			is >> temp;
			if(temp != ""){
				city.append(" ");
				city.append(temp);
			}
			temp = "";
		}

		if(city[city.size() - 1] == ' ')
			city.erase(city.size() - 1);
		*/

		build_strings(line, upc, quant, city);

		int n = boost::lexical_cast<int>(quant);
		
		warehouse *w = warehouses[city];

		std::string pleaseGod = w->get_city();
		w->receive(upc, shelfLife[upc], n);
		warehouses[city] = w;
	}
	
	/* Iterates through each warehouse object and calls
	 * the get_busiest_day() function for the warehouse.
	 * Prints the results returned by the function called
	 * upon warehouse.
	 */
	void data_helper::get_busiest_days(){
		std::cout << "\nBusiest days:" << std::endl;

		typedef std::map<std::string, warehouse*>::iterator it_type;
		for(it_type iterator = warehouses.begin(); iterator != warehouses.end(); iterator++){
			std::cout << iterator->second->get_busiest_day() << std::endl;	
		}
	}

	/* Initializes the start date for the inventory
	 * simulation. 
	 */
	void data_helper::set_start(std::string sDate){
		this->startDate = sDate;
	}

	void data_helper::unstocked_products(){
		std::cout << "\nUnstocked Products:" << std::endl;
		
		bool inStock = false;

		typedef std::map<std::string, std::string>::iterator it_type;
		for(it_type iterator = codeNames.begin(); iterator != codeNames.end(); iterator++){
			
			for(std::map<std::string, warehouse*>::iterator it = warehouses.begin(); it != warehouses.end(); ++it){			
				if(it->second->in_stock(iterator->first))
					inStock = true;
			}
			if(!inStock)
				std::cout << iterator->first << " " << iterator->second << std::endl;
			inStock = false;
		}
	}

	void data_helper::fully_stocked_products(){
		std::cout << "\nFully-Stocked Products:" << std::endl;

		bool inStock = true; 

		typedef std::map<std::string, std::string>::iterator it_type;
		for(it_type iterator = codeNames.begin(); iterator != codeNames.end(); iterator++){
			
			for(std::map<std::string, warehouse*>::iterator it = warehouses.begin(); it != warehouses.end(); ++it){			
				bool val = it->second->in_stock(iterator->first);	
				if(!it->second->in_stock(iterator->first))
					inStock = false;
			}
			if(inStock)
				std::cout << iterator->first << " " << iterator->second << std::endl;
			inStock = true;
		}
	}

	void data_helper::build_strings(std::string &line, std::string &upc, std::string &quant, std::string &city){
		std::istringstream is(line);
		std::string temp;

		is >> upc;
		is >> quant;
		is >> city;
		
		while(!is.fail()){
			is >> temp;
			if(temp != ""){
				city.append(" ");
				city.append(temp);
			}
			temp = "";
		}

		if(city[city.size() - 1] == ' ')
			city.erase(city.size() - 1);
	}

	//------------------ DEBUG METHOD DEFINITIONS --------//
	int data_helper::get_shelflife(std::string upc){
		return 0;
	}
	std::string data_helper::get_code(std::string upc){
		return "Hello";
	}
	std::string data_helper::get_startdate(){
		/*
		typedef std::map<std::string, warehouse*>::iterator it_type;
		for(it_type iterator = warehouses.begin(); iterator != warehouses.end(); iterator++){
			std::string temp = iterator->second->get_busiest_day();
			std::cout << "hello and date is: " << temp << std::endl;
		}
		*/
		return startDate;
	}
}
