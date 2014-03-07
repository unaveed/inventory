/* Author: Umair Naveed and Celeste Hollenbeck
 * January 31, 2014
 *
 */
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "date.h"

namespace inventory { 
	date::date (std::string mdy){
		this->month = boost::lexical_cast<int>(mdy.substr(0,2));
		this->day = boost::lexical_cast<int>(mdy.substr(3,2));
		this->year = boost::lexical_cast<int>(mdy.substr(6,4));
	}

	std::string date::get_date(){
		std::string result;
		int params[3] = {month, day, year};
		for(int i=0; i < 3; i++){
			int num = params[i];
			std::ostringstream convert;
			convert << num;
			
			std::string temp = convert.str();
			if(i < 2)
				temp.append("/");
			result.append(temp);
		}
		return result;
	}

	/** Increments the date in the calendar by
	  * one day. Takes care of leap years and
	  * cases where one more day iterates months
	  * and years.
	  */
	void date::add_day(){
		if(day > 27){
			// Check for months with 30 days
			if(!is_thirty_one()){
				// Deal with february specifically
				if(month == 2){
					if(is_leap_year()){
						if(day == 29){
							month++;
							day = 1;
						}
						else
							day++;
					}
					else {
						day = 1;
						month++;
					}
				}
				else {
					if(day < 30)
						day++;
					else{
						month++;
						day =1;
					}
				}
			}
			// Check for months with 31 days
			else {
				if(day < 31)
					day++;
				else {
					if(month == 12){
						month = 1;
						day = 1;
						year++;
					}
					else{ 
						month++;
						day = 1;
					}
				}
			}
		}
		else 
			day++;
	}

	/** Helper method to determine if the current 
	  * month has 31 days. True if it does, false
	  * if it is a February or a month with 30 days.
	  */
	bool date::is_thirty_one(){
		if(month < 8 && month % 2 != 0)
			return true;
		if(month > 7 && month % 2 == 0)
			return true;
		return false;
	}

	/** Helper method to determine if the current
	  * year is a leap year
	  */
	bool date::is_leap_year(){
		return (year % 4 == 0);
	}

	int main() {
		std::string dayt = "01/31/2012";
		std::string day2 = "01/31/2012";

		date d(dayt);
		date d1(day2);

		std::cout << d.get_date() << std::endl;

		d.add_day();
		std::cout << d.get_date() << std::endl;
		d.add_day();
		std::cout << d.get_date() << std::endl;

		d.add_day();
		std::cout << d.get_date() << std::endl;

		d.add_day();
		std::cout << d.get_date() << std::endl;

		d.add_day();
		std::cout << d.get_date() << std::endl;
	}
}
