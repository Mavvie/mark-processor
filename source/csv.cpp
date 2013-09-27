#include "../include/csv.h"

CSV::CSV()
{
  _file_path = new char[MAX_FILENAME_LENGTH];
  _file_path[0] = 0;
}

CSV::~CSV()
{
  delete[] _file_path;
}

bool CSV::read(const char* lpFn)
{
  strcpy(_file_path, lpFn);
  cout << "Reading file: \"" << _file_path << "\"" << endl; 
  ifstream file;
  file.open(_file_path);
  char line_buffer[MAX_ROW_LENGTH] = "";

  file.getline(line_buffer, MAX_ROW_LENGTH);

  while(!file.eof())
  {
    // cout << "Raw CSV line: " << line_buffer << endl;
    vector<char*> *new_row = new vector<char*>;
    char* pch = strtok(line_buffer, ";");
    while(pch != NULL)
    {
      char *new_column = new char[MAX_COLUMN_LENGTH];
      strcpy(new_column, pch);
      new_row->push_back(new_column);
      pch = strtok(NULL, ";");
    }
    _rows.push_back(new_row);
    file.getline(line_buffer, MAX_ROW_LENGTH);
  }

  file.close();
}

const char* CSV::file_path()
{
  return _file_path;
}

vector<vector<char*>*>* CSV::rows()
{
  return &_rows;
}