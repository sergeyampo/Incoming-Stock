#ifndef GUARD_INVOICE_H
#define GUARD_INVOICE_H

#include "Good.h"
#include "Date.h"
#include <list>

struct Invoice{
  std::list<std::pair<Good, uint32_t> > goods_list;
  uint64_t id;
  Date date;
  std::string supplier_name;
};

#endif