#ifndef GUARD_IOSTOCK_H
#define GUARD_IOSTOCK_H

#include "Invoice.h"

namespace IOStock{

Invoice ConstructInvoice(std::istream&, std::ostream&);
char InvoiceChooseAction();
std::pair<Good, uint32_t> ConstructGood(std::istream&, std::ostream&);

};

#endif