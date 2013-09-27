#pragma once

#include "csv.h"

class HarrizCSV : public CSV {
public:
  bool read(const char* lpFn);
  vector<char*> *headers();
private:
  vector<char*> _headers;
};