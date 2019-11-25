#ifndef GUARD_DATE_H
#define GUARD_DATE_H

#include <cstdint>
#include <string_view>
#include <iostream>
#include <cmath>

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

std::istream& operator>>(std::istream& in, Date& d) { return d.input(in); }
std::ostream& operator<<(std::ostream& out, const Date& d) { return d.print(out); }


Date GetDateByString(const std::string& strdate){
  		Date ret;
  		std::string_view s(strdate);
  		
  		auto f_dot = s.find(".");
  		ret.SetDay(std::stoi(std::string(s.substr(0, f_dot))));

  		auto s_dot = s.find(".", f_dot+1);
  		ret.SetMonth(std::stoi(std::string(s.substr(f_dot+1, s_dot))));

  		auto t_dot = s.find(".", s_dot+1);
  		ret.SetYear(std::stoi(std::string(s.substr(s_dot+1, t_dot))));

  		return ret;
}

std::istream& Date::input(std::istream& in){
  std::string str;
  in >> str;

  *this = GetDateByString(str);
        
  return in;
}

std::ostream& Date::print(std::ostream& out) const{

 out << (std::string)*this;

 return out;
}

#endif