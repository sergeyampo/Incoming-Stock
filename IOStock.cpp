#include "IncomingStock.h"
#include "Good.h"
#include "CorrectInput.h"
#include "IOStock.h"

using namespace std;

namespace IOStock{
/**
* @brief Constructs Invoice object interactively via console.
*/
Invoice ConstructInvoice(istream& in, ostream& out){
	out << "Enter the id of the invoice: ";
	uint64_t id = CorrectInput::EnterIntNum();

	out << "Enter the date in format dd.m.year: ";
	Date d;
	in >> d;

	out << "Enter the name of the supplier: ";
	string supplier_name;
	in >> supplier_name;


	out << "Now you should fullfiled info about goods you want to\n" <<
           "add to the stock.\n";
    list<pair<Good, uint32_t> > goods;

    char choice = InvoiceChooseAction();
    while(choice == '1'){
      goods.emplace_back(ConstructGood(in, out));
      choice = InvoiceChooseAction();
    }
    
    return {goods, id, d, supplier_name};

}

/**
* @brief Help function for ConstructInvoice
* @see ConstructInvoice()
*/
char InvoiceChooseAction(){
	cout <<
		"Choose an action:\n" <<
		"1)Add new good\n" <<
		"2)Exit\n" <<
		"Enter number: ";
	char choice;
	cin >> choice;
	system("CLS");

	if (choice == '1' || choice == '2') return choice;
	
	else 
		return InvoiceChooseAction();

	return '0';
}

/**
* @brief Constructs Good object interactively via console.
*/
Good ConstructGood(istream& in, ostream& out){
	out << "Enter the name and the price of good with space.\n" <<
	       "Enter: ";
	Good g;
	in >> g.name >> g.price;

	return g;
}
}