#include "../include/harrizcsv.h"
#include "../include/mark.h"
#include "../include/student.h"

using namespace std;

int main() {
  HarrizCSV* csv = new HarrizCSV();
  csv->read("data/SCHS21-1.csv");
  vector<Student*> students;

  vector<vector<char*>*>* prows = csv->rows();

  int rows = prows->size();

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

  // PRINT ALL DATA IN MEMORY
  // for(int row = 0; row < rows; row++)
  // {
  //   vector<char*>* columns = prows->at(row);
  //   for(int column = 0; column < columns->size(); column++)
  //   {
  //     cout << columns->at(column);
  //     if(column + 1 < columns->size())
  //       cout << ";";
  //   }
  //   cout << endl;
  // }

  cout << "\n\nHeaders found:\n\n";
  vector<char*> *headers = csv->headers();
  for(int row = 0; row < prows->size(); row++)
  {
    Student *new_student = new Student;
    vector<char*>* columns = prows->at(row);
    new_student->Type = new char[20];
    strcpy(new_student->Type, columns->at(0));
    new_student->a = new char[20];
    strcpy(new_student->a, columns->at(1));
    for(int col = 2; col < columns->size(); col++)
    {
      if(strcmp(headers->at(col), "O.A") == 0)
      {
        new_student->OAs.push_back(Mark(columns->at(col)));
      }
    }
    students.push_back(new_student);
  }

  for(int i=0; i<students.size(); i++)
  {
    Student* student = students.at(i);
    float sum = 0.0f;
    cout << "Student # " << i << endl;
    for(int ioa = 0; ioa < student->OAs.size(); ioa++)
    {
      sum += student->OAs.at(ioa).to_int();
      cout << "O.A: " << student->OAs.at(ioa).to_int() << endl;
    }
    float average = sum / float(student->OAs.size());
    cout << "Average mark: " << average << endl << endl << endl;
  }

  ofstream outfile("output.csv");

  outfile << endl << endl;

  for(int i=0; i<students.size(); i++)
  {
    Student* student = students.at(i);
    float sum = 0.0f;
    outfile << student->Type << ";" << student->a;
    for(int ioa = 0; ioa < student->OAs.size(); ioa++)
    {
      sum += student->OAs.at(ioa).to_int();
      outfile << ";" << student->OAs.at(ioa).to_string();
    }
    float average = sum / float(student->OAs.size());
    outfile << ";" << average << endl;
  }

  outfile.close();

  return 0;
}