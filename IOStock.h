#ifndef GUARD_IOSTOCK_H
#define GUARD_IOSTOCK_H

#include "Invoice.h"
#include "stdint.h"
#include <list>
#include <string>

namespace IOStock{
Invoice ConstructInvoice(std::istream&, std::ostream&);
char InvoiceChooseAction();
std::pair<Good, uint32_t> ConstructGood(std::istream&, std::ostream&);
std::list<std::pair<Good, uint32_t> >::iterator DialogueFindGood(std::istream&, std::ostream&, IncomingStock&, const std::string&);
};

#endif