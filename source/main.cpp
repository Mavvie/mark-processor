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
  int columns = prows->at(0)->size();

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
      else if(strncmp(headers->at(col), "E", 1) == 0)
      {
        new_student->Exams.push_back(Mark(columns->at(col)));
      }
      else if(strncmp(headers->at(col), "S", 1) == 0)
      {
        new_student->Summatives.push_back(Mark(columns->at(col)));
      }
    }
    students.push_back(new_student);
  }

  for(int i=0; i<students.size(); i++)
  {
    Student* student = students.at(i);
    // float sum = 0.0f;
    cout << "Student # " << i << endl;
    for(int ioa = 0; ioa < student->OAs.size(); ioa++)
    {
      // sum += student->OAs.at(ioa).to_int();
      cout << "O.A: " << student->OAs.at(ioa).to_int() << endl;
    }
    for(int ie = 0; ie < student->Exams.size(); ie++)
    {
      int exmark = student->Exams.at(ie).to_int();
      if(exmark < 0)
        cout << "Exam: Absent" << endl;
      else
        cout << "Exam: " << exmark << endl;
    }
    for(int is = 0; is < student->Summatives.size(); is++)
    {
      cout << "Summative: " << student->Summatives.at(is).to_int() << endl;
    }
    // float average = sum / float(student->OAs.size());
    cout << "First 3 terms mark: " << student->term_mark(3).to_int() << endl << endl << endl;
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