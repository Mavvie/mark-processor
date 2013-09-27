#include "../include/harrizcsv.h"

bool HarrizCSV::read(const char* lpFn)
{
  strcpy(_file_path, lpFn);
  cout << "Reading file (harriz): \"" << _file_path << "\"" << endl; 
  ifstream file;
  file.open(_file_path);
  char line_buffer[MAX_ROW_LENGTH] = "";

  file.getline(line_buffer, MAX_ROW_LENGTH);

  bool start_reading = false;

  while(!file.eof() && file.good())
  {
    if(strcmp(line_buffer, "Type") >= 4 && start_reading == false)
    {
      // Initialize headers and tell to start reading
      char* pch = strtok(line_buffer, ";");
      while(pch != NULL)
      {
        char* new_header = new char[MAX_COLUMN_LENGTH];
        strcpy(new_header, pch);
        _headers.push_back(new_header);
        pch = strtok(NULL, ";");
      }
      start_reading = true;
      file.getline(line_buffer, MAX_ROW_LENGTH);
      continue;
    }
    if(start_reading == false)
    {
      file.getline(line_buffer, MAX_ROW_LENGTH);
      continue;
    }
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

vector<char*> *HarrizCSV::headers()
{
  return &_headers;
}