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

	system("CLS");
	out << "Please add first item to the invoice:\n";
	goods.emplace_back(ConstructGood(in, out));
	system("CLS");
	
	char choice;
    do{
      goods.emplace_back(ConstructGood(in, out));
      choice = InvoiceChooseAction();
	} while (choice == '1');
    
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
pair<Good, uint32_t> ConstructGood(istream& in, ostream& out){
	out << "Enter the name, the price and the amount of good with space.\n" <<
	       "Enter: ";
	Good g;
	uint32_t amount;
	in >> g.name >> g.price >> amount;
	

	return make_pair(g, amount);
}

/**
* @brief Makes a dialogue of seeking a good item in a stock, telling if it wasn't found.
* @param stock - stock of goods.
* @param name - the name of good to find. 
* @return iterator - points to the element we found or stock.end() if it's not.
*/
std::list<std::pair<Good, uint32_t> >::iterator DialogueFindGood(istream& in, ostream& out, IncomingStock& stock, const string& name) {
	if (auto found = stock.StockFindGoodByName(name); found != stock.end()) {
		streamsize prec = out.precision();
		out << "Found element: " << found->first.name << " " << setprecision(3) << found->first.price << streamsize(prec) << "\n";
		CorrectInput::WaitEnter(in, out);
		return found;
	}
	else {
		out << "Nothing was found!\n";
		CorrectInput::WaitEnter(in, out);
		return stock.end();
	}
}
}