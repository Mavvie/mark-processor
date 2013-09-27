#pragma once

#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Mark {
public:
  Mark();
  Mark(int mark);
  Mark(char* str);
  char* to_string();
  int to_int();
private:
  char* _str;
  int _int;
};