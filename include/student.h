#pragma once

#include "mark.h"
#include <vector>

using namespace std;

class Student {
public:
  vector<Mark> OAs;
  vector<Mark> Exams;
  vector<Mark> Summatives;
  Mark final_mark();
  Mark final_mark(int units);
  Mark term_mark(int units);
  Mark term_mark();
  Mark exam_mark();
  Mark summative_mark();
  char* Type;
  char* a;
};