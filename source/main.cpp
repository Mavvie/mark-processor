#include "../include/harrizcsv.h"

using namespace std;

int main() {
  HarrizCSV* csv = new HarrizCSV();
  csv->read("data/SCHS21-1.csv");

  vector<vector<char*>*>* prows = csv->rows();

  int rows = prows->size();
  // cout << "Rows: " << rows << endl;

  // for(int row = 0; row < rows;)
  // {
  //   vector<char*>* columns = prows->at(row);
  //   if(columns->size() > 0)
  //   {
  //     if(strcmp(columns->at(0), "Type") == 0)
  //     {
  //       break;
  //     }
  //   }
  //   prows->erase(prows->begin());
  // }



  // cout << "Printing how it's arranged in memory: \n\n";

  rows = prows->size();
  cout << "Rows: " << rows << endl;

  if(rows == 0)
  {
    cout << "No rows found in CSV file...aborting" << endl;
    return 1;
  }

  int columns = prows->at(0)->size();
  cout << "Columns: " << columns << endl;

  if(columns == 0)
  {
    cout << "No columns found in CSV file...aborting" << endl;
    return 2;
  }

  for(int row = 0; row < rows; row++)
  {
    vector<char*>* columns = prows->at(row);
    for(int column = 0; column < columns->size(); column++)
    {
      cout << columns->at(column);
      if(column + 1 < columns->size())
        cout << ";";
    }
    cout << endl;
  }

  cout << "\n\nHeaders found: \n\n";
  vector<char*> *headers = csv->headers();
  for(int i = 0; i < headers->size(); i++)
  {
    cout << headers->at(i) << " : ";
    cout << prows->at(0)->at(i) << endl;
  }

  return 0;
}