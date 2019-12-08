#ifndef GUARD_INCOMING_STOCK_H
#define GUARD_INCOMING_STOCK_H

#include "Invoice.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "CppConsoleTable.hpp"

/**
* @brief Enumeration class helps us to distinguish the way of printing the file.
*/
enum class PrintView {
	file = 0,
	table
};

class IncomingStock{
  public:
    using list_of_cnt_goods = std::list<std::pair<Good, uint32_t>>;
    
	IncomingStock() = default;
	IncomingStock(const IncomingStock&) = default;
	///Constructor by filename
	explicit IncomingStock(const std::string&);
	IncomingStock(const list_of_cnt_goods& ls, const std::vector<Invoice>& invs) : data(ls), invoices(invs) { } 
	IncomingStock(IncomingStock&&) = default;

   ~IncomingStock() = default;
    
    ///Manage invoice by adding goods to stock.
    void ManageInvoice(const Invoice&);
    ///Adding passed invoice to the vector of invoices.
	void AddInvoice(const Invoice&);

    ///Read from any stream like file or cin
    std::istream& Read(std::istream&);
    ///Write to any strem like file or cout
    std::ostream& Write(std::ostream&, PrintView) const;
	///Write to any stream in a table view
	std::ostream& WriteTable(std::ostream&) const;
	///Write list of goods to ConsoleTable object
	samilton::ConsoleTable AddGoodsToTable(samilton::ConsoleTable&, const IncomingStock::list_of_cnt_goods&) const;
    ///Return iterator points to the pair with name concurrence or end(data) if nothing was found.
    list_of_cnt_goods::iterator StockFindGoodByName(const std::string&);

    //Iterators
    list_of_cnt_goods::iterator begin() { return data.begin(); }
    list_of_cnt_goods::const_iterator begin() const { return data.cbegin(); }
    list_of_cnt_goods::iterator end() { return data.end(); }
    list_of_cnt_goods::const_iterator end() const { return data.cend(); }

	IncomingStock& operator=(const IncomingStock&) = default;

  private:
  	list_of_cnt_goods data;
  	std::vector<Invoice> invoices;

  private:
  	std::istream& ReadToListOfGoods(std::istream&, list_of_cnt_goods&, const list_of_cnt_goods::size_type&);
    std::istream& ReadToListOfInvoices(std::istream&, std::vector<Invoice>&, const std::vector<Invoice>::size_type&);
    std::ostream& WriteListOfGoods(std::ostream& out, const list_of_cnt_goods&) const;
};

std::istream& operator>>(std::istream&, IncomingStock&);
std::ostream& operator<<(std::ostream&, IncomingStock&);

#endif