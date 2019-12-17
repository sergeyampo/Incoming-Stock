#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace CorrectInput {
	void ClearCin(std::istream&);

	std::string EnterSym();

	double EnterDoubleNum();

	unsigned int EnterIntNum();

	std::istream& WaitEnter(std::istream&, std::ostream&);
};
