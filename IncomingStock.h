#ifndef GUARD_INCOMING_STOCK_H
#define GUARD_INCOMING_STOCK_H

#include "Invoice.h"
#include <vector>
#include <iostream>

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
    void AddInvoice(const Invoice& inv) { invoices.emplace_back(inv); };

    ///Read from any stream like file or cin
    std::istream& Read(std::istream&);
    ///Write to any strem like file or cout
    std::ostream& Write(std::ostream&) const;
    
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

#endif