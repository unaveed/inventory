/* Author: Umair Naveed and Celeste Hollenbeck
 * January 31, 2014
 *
 */
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "date.h"

namespace inventory 
{
date::date (std::string mdy){
	this->month = boost::lexical_cast<int>(mdy.substr(0,2));
	this->day = boost::lexical_cast<int>(mdy.substr(3,2));
	this->year = boost::lexical_cast<int>(mdy.substr(6,4));
}

/* Converts a date object into a 
 * string in the following format
 * MM/DD/YYYY. 
 */
std::string date::get_date(){
	// Flag to see if a number is single digits so that
	// a 0 can be appended to it
	bool singleDigit = false;

	// Holds the resultant string
	std::string result;
	int params[3] = {month, day, year};

	for(int i=0; i < 3; i++){
		int num = params[i];

		// Set flag if number is single digits
		if(num < 10)
			singleDigit = true;

		std::ostringstream convert;
		convert << num;
	
		// Convert integer to a string
		std::string temp = convert.str();

		// Preappend "0" for digits less than 0
		if(singleDigit)
			temp.insert(0, "0");
		if(i < 2)
			temp.append("/");
		result.append(temp);

		// Reset flag value
		singleDigit = false;
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

bool date::operator> (date &rhs){
	std::string sd1 = get_date();
	std::string sd2 = rhs.get_date();
	
	int m1 = boost::lexical_cast<int>(sd1.substr(0,1));
    int m2 = boost::lexical_cast<int>(sd1.substr(3,2));
    int m3 = boost::lexical_cast<int>(sd1.substr(6,4));

    int m21 = boost::lexical_cast<int>(sd2.substr(0,2));
    int m22 = boost::lexical_cast<int>(sd2.substr(3,2));
    int m23 = boost::lexical_cast<int>(sd2.substr(6,4));

    if(m23 > m3)
    	return false;
	if(m22 > m2)
		return false;
	if(m21 > m1)
		return false;

    return true;
}

/*
int main() {
	std::string dayt = "01/31/2012";
	date d(dayt);
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

}*/
}

