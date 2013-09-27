#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_FILENAME_LENGTH   ((int)256)
#define MAX_ROW_LENGTH      ((int)1024)
#define MAX_COLUMN_LENGTH   ((int)512)

class CSV {
public:
  CSV();
  CSV(const char* lpFn);
  ~CSV();
  virtual bool read(const char* lpFn);
  const char* file_path();
  vector<vector<char*>*>* rows();
  char* _file_path;
  vector<vector<char*>*> _rows;
private:
};