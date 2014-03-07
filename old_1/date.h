#ifndef DATE_H
#define DATE_H
#include <string>

namespace inventory {
	class date {
	private:
		int year;
		int month;
		int day;
		bool is_thirty_one();
		bool is_leap_year();
	public:
		date (std::string);	// Constructor
		date (const date & other);	// Copy constructor
		std::string get_date();
		void add_day();
		int compare_to(std::string);
	};
}
#endif
