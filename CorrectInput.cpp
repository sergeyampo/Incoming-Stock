#include <iostream>
#include <string>
#include <sstream>
#include "CorrectInput.h"

using namespace std;

namespace CorrectInput {
	void ClearCin(std::istream& in) {
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}



	string EnterSym() {
		string text;
		while (true) {
			bool key = 1;
			cin >> text;
			for (string::const_iterator beg = text.cbegin(); beg != text.cend(); ++beg)
				if (isalpha(*beg) == false)//проверка каждого символа на букву
					key = 0;
			if (key == 0)
				cout << "Enter text again: ";
			else
				return text;
		}
		return text;

	}

	double EnterDoubleNum()
	{
		while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
		{
			double a;
			cin >> a;
			if (cin.fail() or a < 0) // если предыдущее извлечение оказалось неудачным,
			{
				cin.clear(); // то возвращаем cin в 'обычный' режим работы
				cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
				cout << "Enter number again: ";
			}

			else // если всё хорошо, то возвращаем a
				return a;
		}
	}
	unsigned int EnterIntNum()
	{
		while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
		{
			unsigned int a;
			cin >> a;
			if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
			{
				cin.clear(); // то возвращаем cin в 'обычный' режим работы
				cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
				cout << "Enter number again: ";
			}
			else // если всё хорошо, то возвращаем a
				return a;
		}
	}

	istream& WaitEnter(istream& in, ostream& out) {
		out << "Press the enter to continue...";
		ClearCin(in);
		in.get();

		return in;
	}
};
