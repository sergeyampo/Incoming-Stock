#include "IncomingStock.h"
#include "Date.h"
#include <fstream>
#include <type_traits>

using namespace std;
using ConsoleTable = samilton::ConsoleTable;

/**
* @brief Constructs class from the file with `filename` name.
* @see IncomingStock::Read()
* @throws invalid_argument Thrown if `filename` wouldn't be found.
* @param filename the name of the file
*/
IncomingStock::IncomingStock(const string& filename){
	ifstream fin(filename.c_str());

	if(!fin.is_open())
		throw invalid_argument("File with such name wasn't found.");

	Read(fin);
}

/**
* @brief Manage invoice by increasing current amount of goods or creating ones.
* @param inv invoice object to manage.
* 
*/
void IncomingStock::ManageInvoice(const Invoice& inv){
  for(const pair<Good, uint32_t>& p : inv.goods_list){
  	  //If we found good in stock with the same name as in invoice
  	  //increase its amount otherwise add this good.
      if(auto found = StockFindGoodByName(p.first.name); found != data.end())
        found->second += p.second;
      else
      	data.emplace_back(p);
  }
}

/**
* @brief Fullfit current object with content by `in` stream.
* @details It reads line by line by several rules: first line is an amount
* of goods in a stock = N. Next N lines has content like: "name_of_good amount price"
* N+1 line is an amount of invoices = K.
* N+2 line has content "id date supplier_name".
* N+3 line is an amount of goods in this invoice = M.
* And next M lines has conent like: "name_of_good amount price"
* If K >= 1 we'll continue.
*/
std::istream& IncomingStock::Read(std::istream& in){
	list_of_cnt_goods::size_type sz = 0;
	in >> sz;
	ReadToListOfGoods(in, data, sz);
	
   	size_t inv_amnt = 0;
   	in >> inv_amnt;
   	
   	ReadToListOfInvoices(in, invoices, inv_amnt);

   	return in;
}


///Reads `sz` elements of pairs to the `list` container.
std::istream& IncomingStock::ReadToListOfGoods(istream& in, IncomingStock::list_of_cnt_goods& list, const IncomingStock::list_of_cnt_goods::size_type& sz){
	for (auto i = decltype(sz){1}; i <= sz; ++i) {
	  string name;
	  uint32_t amount;
	  float price;
	  in >> name >> amount >> price;
	  list.push_back(pair<Good, uint32_t>(Good{name, price}, amount));
	}

	return in;
}

///Reads `sz` elements of Invoices which contains list of goods and some invoice's info.
std::istream& IncomingStock::ReadToListOfInvoices(istream& in, std::vector<Invoice>& list, const std::vector<Invoice>::size_type& sz){
	for(auto i = 1; i <= sz; ++i){
	  uint64_t id;
	  Date date;
	  string name;
	  in >> id >> date >> name;

	  list_of_cnt_goods::size_type inv_g_sz = 0;
	  in >> inv_g_sz;
	  list_of_cnt_goods curr_invoices_goods;

	  ReadToListOfGoods(in, curr_invoices_goods, inv_g_sz);
	  list.push_back({curr_invoices_goods, id, date, name});
    }

    return in;
}

/**
* @brief Print content of current object in Read style.
* @see IncomingStock::Read()
*/
std::ostream& IncomingStock::Write(std::ostream& out, PrintView method = PrintView::file) const{
	if (method == PrintView::table)
		WriteTable(out);
	
	else {
		out << data.size() << "\n";

		WriteListOfGoods(out, data);

		out << invoices.size() << "\n";

		for (auto& inv : invoices) {
			out << inv.id << " " << inv.date << " " << inv.supplier_name << "\n";
			WriteListOfGoods(out, inv.goods_list);
		}
	}

    return out;
}

///Function add rows with list of countable goods info in a passed ConsoleTable object.
ConsoleTable IncomingStock::AddGoodsToTable(ConsoleTable& table_goods, const IncomingStock::list_of_cnt_goods& goods) const {
	table_goods.addRow(vector<string>{ "Name", "Price", "Amount" });
	for (const pair<Good, uint32_t>& i : goods) {
		vector<string> line = { i.first.name, to_string(i.first.price), to_string(i.second) };
		table_goods.addRow(line);
	}
	
	return table_goods;
}

///Make the same things as IncomingStock::Write but in a table view way.
ostream& IncomingStock::WriteTable(ostream& out) const {
	ConsoleTable table(samilton::Alignment::centre);
	table[0][1] = "Stock's good:";
	table = AddGoodsToTable(table, data);

	table.addRow(vector<string>{ "*", "Invoices:", "*" });
	for (auto& inv : invoices) {
		table.addRow(vector<string>{ "ID", "Date", "Supplier Name" });
		table.addRow(vector<string>{to_string(inv.id), static_cast<string>(inv.date), inv.supplier_name});
		table.addRow(vector<string>{ "*", "Invoices'es goods:", "*" });
		AddGoodsToTable(table, inv.goods_list);
	}

	out << table;

	return out;
}

///Write list of goods to ConsoleTable object
std::ostream& IncomingStock::WriteListOfGoods(ostream& out, const IncomingStock::list_of_cnt_goods& list) const {
	for (auto& el : list)
		out << el.first.name << " " << el.second << " " << el.first.price << "\n";

	return out;
}

///Find element in a list of pairs of Goods and its amounts by name.
std::list<std::pair<Good, uint32_t> >::iterator IncomingStock::StockFindGoodByName(const std::string& name){
	return find_if(begin(), end(), [&name](const std::pair<Good, uint32_t>& x) { return name == x.first.name; });
}

///Adding new invoice in a vector if id is unique.
void IncomingStock::AddInvoice(const Invoice& inv) {
	if (std::find_if(invoices.begin(), invoices.end(), [inv](const auto& p) { return p.id == inv.id;  }) != invoices.end())
		throw invalid_argument("The id of the new invoice should be unique!");
	
	invoices.emplace_back(inv);
}

std::istream& operator>>(std::istream& in, IncomingStock& stock) { return stock.Read(in); }
std::ostream& operator<<(std::ostream& out, IncomingStock& stock) { return stock.Write(out); }