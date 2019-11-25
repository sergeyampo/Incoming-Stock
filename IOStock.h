#ifndef GUARD_IOSTOCK_H
#define GUARD_IOSTOCK_H

#include "Invoice.h"

namespace IOStock{

Invoice ConstructInvoice(std::istream&, std::ostream&);
char InvoiceChooseAction();
Good ConstructGood(std::istream&, std::ostream&);

};

#endif