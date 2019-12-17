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
				if (isalpha(*beg) == false)//�������� ������� ������� �� �����
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
		while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ����� ���������� ��������
		{
			double a;
			cin >> a;
			if (cin.fail() or a < 0) // ���� ���������� ���������� ��������� ���������,
			{
				cin.clear(); // �� ���������� cin � '�������' ����� ������
				cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
				cout << "Enter number again: ";
			}

			else // ���� �� ������, �� ���������� a
				return a;
		}
	}
	unsigned int EnterIntNum()
	{
		while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ����� ���������� ��������
		{
			unsigned int a;
			cin >> a;
			if (cin.fail()) // ���� ���������� ���������� ��������� ���������,
			{
				cin.clear(); // �� ���������� cin � '�������' ����� ������
				cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
				cout << "Enter number again: ";
			}
			else // ���� �� ������, �� ���������� a
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
