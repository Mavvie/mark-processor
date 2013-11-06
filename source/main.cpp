#include "../include/harrizcsv.h"
#include "../include/mark.h"
#include "../include/student.h"
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
  cout << getcwd(0,0) << endl;
  char *lpFn = new char[1024];
  char *only = new char[256];
  char *exclude = new char[256];
  char *outputFn = new char[1024];

  strcpy(lpFn, "data/SCHS21-1.csv");
  strcpy(outputFn, "data/output.csv");
  strcpy(only, "");
  strcpy(exclude, "");

  int n_terms = 0;
  char c;
  while((c = getopt(argc, argv, ":f:n:e:i:o")) != -1)
  {
    switch(c)
    {
      case 'f':
        strncpy(lpFn, optarg, 256);
        break;
      case 'n':
        sscanf(optarg, "%d", &n_terms);
        break;
      case 'e':
        strncpy(exclude, optarg, 256);
        break;
      case 'i':
        strncpy(only, optarg, 256);
        break;
      case 'o':
        strncpy(outputFn, optarg, 256);
        break;
      case '?':
        if(optopt == 'f' || optopt == 'n' || optopt == 'e' || optopt == 'i')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else
          fprintf(stderr, "Unknown option %c.\n", optopt);
        return 1;
      default:
        break;
    }
  }

  printf("file path: \"%s\"\n", lpFn);
  printf("only: \"%s\"\n", only);
  printf("exclude: \"%s\"\n", exclude);
  printf("n_terms: %d\n", n_terms);

  HarrizCSV* csv = new HarrizCSV();
  csv->read(lpFn);
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
      if(strncmp(headers->at(col), "O.A", 3) == 0)
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
    char* full_name = new char[1024];
    strcpy(full_name, new_student->Type);
    strcat(full_name, new_student->a);

    bool add = true;
    if(strlen(only))
    {
      add = strstr(full_name, only) == 0;
    }
    if(strlen(exclude))
    {
      if(strstr(full_name, exclude) == 0)
        add = false;
    }
    if(add)
      students.push_back(new_student);
  }

  for(int i=0; i<students.size(); i++)
  {
    Student* student = students.at(i);
    cout << "Student name: " << student->Type << " " << student->a << endl;
    for(int ioa = 0; ioa < student->OAs.size(); ioa++)
    {
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
    if(n_terms > 0) {
      cout << "Term mark: " << student->term_mark(n_terms).to_int() << endl;
      cout << "Final mark: " << student->final_mark(n_terms).to_int() << endl << endl << endl;
    }
    else {
      cout << "Term mark: " << student->term_mark().to_int() << endl;
      cout << "Final mark: " << student->final_mark().to_int() << endl << endl << endl;
    }
  }

  ofstream outfile(outputFn);

  int n_summatives = students.at(0)->Summatives.size();
  int n_exams = students.at(0)->Exams.size();
  if(n_terms > 0) {
    outfile << "First name" << ";" << "Last name" << ";";
    for(int i=0; i<n_terms; i++)
      outfile << "O.A" << i+1 << ";";
    for(int i=0; i<n_summatives; i++)
      outfile << "Summative #" << i+1 << ";";
    for(int i=0; i<n_exams; i++)
      outfile << "Exam #" << i+1 << ";";

    outfile << ";;Term mark (" << n_terms << " terms);Final mark" << endl;

    for(int i=0; i<students.size(); i++)
    {
      Student* student = students.at(i);
      outfile << student->Type << ";" << student->a << ";";
      for(int iterm = 0; iterm < n_terms && iterm < student->OAs.size(); iterm++)
        outfile << student->OAs.at(iterm).to_int() << ";";
      for(int isum = 0; isum < n_summatives; isum++)
        outfile << student->Summatives.at(isum).to_int() << ";";
      for(int iex = 0; iex < n_exams; iex++) {
        int exmark = student->Exams.at(iex).to_int();
        if(exmark == -1000000)
          outfile << "A" << ";";
        else
          outfile << exmark << ";";
      }
      outfile << ";;" << student->term_mark(n_terms).to_int() << ";";
      outfile << student->final_mark(n_terms).to_int();
      outfile << endl;
    }
  }
  else
  {
    n_terms = students.at(0)->OAs.size();
    outfile << "First name" << ";" << "Last name" << ";";
    for(int i=0; i<n_terms; i++)
      outfile << "O.A" << i+1 << ";";
    for(int i=0; i<n_summatives; i++)
      outfile << "Summative #" << i+1 << ";";
    for(int i=0; i<n_exams; i++)
      outfile << "Exam #" << i+1 << ";";

    outfile << ";;Term mark (all terms);Final mark" << endl;

    for(int i=0; i<students.size(); i++)
    {
      Student* student = students.at(i);
      outfile << student->Type << ";" << student->a << ";";
      for(int iterm = 0; iterm < student->OAs.size(); iterm++)
        outfile << student->OAs.at(iterm).to_int() << ";";
      for(int isum = 0; isum < n_summatives; isum++)
        outfile << student->Summatives.at(isum).to_int() << ";";
      for(int iex = 0; iex < n_exams; iex++) {
        int exmark = student->Exams.at(iex).to_int();
        if(exmark == -1000000)
          outfile << "A" << ";";
        else
          outfile << exmark << ";";
      }
      outfile << ";;" << student->term_mark(n_terms).to_int() << ";";
      outfile << student->final_mark(n_terms).to_int();
      outfile << endl;
    }
  }

  outfile.close();

  return 0;
}
