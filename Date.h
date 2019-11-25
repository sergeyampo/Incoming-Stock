#ifndef GUARD_DATE_H
#define GUARD_DATE_H

#include <cstdint>
#include <string_view>
#include <iostream>
#include <cmath>
#include <string>

/**
* @brief Date class for julian calendar stuff.
*/
class Date{
  public:
    Date() = default;
    Date(const Date&) = default;
    Date(Date&&) = default;
    Date(const int8_t& d, const int8_t& m, const int_fast32_t& y) : day(d), month(m), year(y) { }
   ~Date() = default;

    operator std::string() const { return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year); }

    int8_t GetDay() const { return day; }
    int8_t GetMonth() const { return month; }
    int_fast32_t GetYear() const { return year; }

    void SetDay(const int8_t& d) { day = d; }
    void SetMonth(const int8_t& m) { month = m; }
    void SetYear(const int_fast32_t& y) { year = y; }
    
	Date& operator=(const Date&) = default;

    ///Prints date in format: dd.m.y
    std::ostream& print(std::ostream&) const;
    ///Reads date in format dd.m.y
    std::istream& input(std::istream&);

  private:
  	int8_t day, month;
  	int_fast32_t year;
};

std::istream& operator>>(std::istream&, Date&);
std::ostream& operator<<(std::ostream&, const Date&);

#endif