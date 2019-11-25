#include <cstdint>
#include <string_view>
#include <iostream>
#include <cmath>
#include "Date.h"

std::istream& operator>>(std::istream& in, Date& d) { return d.input(in); }
std::ostream& operator<<(std::ostream& out, const Date& d) { return d.print(out); }


Date GetDateByString(const std::string& strdate) {
	Date ret;
	std::string_view s(strdate);

	auto f_dot = s.find(".");
	ret.SetDay(std::stoi(std::string(s.substr(0, f_dot))));

	auto s_dot = s.find(".", f_dot + 1);
	ret.SetMonth(std::stoi(std::string(s.substr(f_dot + 1, s_dot))));

	auto t_dot = s.find(".", s_dot + 1);
	ret.SetYear(std::stoi(std::string(s.substr(s_dot + 1, t_dot))));

	return ret;
}

std::istream& Date::input(std::istream& in) {
	std::string str;
	in >> str;

	*this = GetDateByString(str);

	return in;
}

std::ostream& Date::print(std::ostream& out) const {

	out << (std::string)*this;

	return out;
}