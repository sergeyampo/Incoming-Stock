#include <fstream>
#include <sstream>
#include <iomanip>
#include "IncomingStock.h"
#include "CorrectInput.h"
#include "IOStock.h"

using namespace std;

char ChooseFirstAction() {
	system("CLS");
	cout <<
		"Choose an action:\n" <<
		"1)Read from file\n" <<
		"2)Create Invoice\n" <<
		"3)Save to file\n" <<
		"4)Find by name\n" <<
		"5)Print\n"
		"6)Exit\n"<<
		"Enter number: ";
	char choice;
	cin >> choice;
	system("CLS");

	if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6') return choice;
	else { CorrectInput::ClearCin(cin); return ChooseFirstAction(); }

	return '0';
}

int main(){
	IncomingStock stock;
	bool is_exit = false;

	do{
	char choice = ChooseFirstAction();
	
	if(choice == '1'){
	  cout << "Enter the name of the file: ";
	  string filename = CorrectInput::EnterSym();
	  try{
	    stock = IncomingStock(filename);
	  }
	  catch(invalid_argument e){
	  	cout << e.what() << endl;
	  }
	}
	
	else if(choice == '2'){
    	Invoice inv = IOStock::ConstructInvoice(cin, cout);
    	stock.ManageInvoice(inv);
		try {
			stock.AddInvoice(inv);
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}
    }

    else if(choice == '3'){
		cout << "Enter the name of the file: ";
    	string filename = CorrectInput::EnterSym();
    	ofstream fout(filename.c_str());

		fout << stock;
    	cout << "The data was successfully written to the file!\n";
    }

    else if(choice == '4'){
		cout << "Enter the name of the good: ";
    	string name = CorrectInput::EnterSym();
    	if(auto found = stock.StockFindGoodByName(name); found != stock.end()){
    	  streamsize prec = cout.precision();
    	  cout << "Found element: " << found->first.name << " " << setprecision(3) << found->first.price << streamsize(prec) << "\n";
    	}
    	else{
    		cout << "Nothing was found!\n";	
    	}
    }

	else if (choice == '5') {
		stock.Write(cout, PrintView::table);
	}

    else
      is_exit = true;    

    } while(!is_exit);

	return 0;
}