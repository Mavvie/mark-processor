#pragma once

#include "mark.h"
#include <vector>

using namespace std;

class Student {
public:
  vector<Mark> OAs;
  Mark final_mark;
  char* Type;
  char* a;
};