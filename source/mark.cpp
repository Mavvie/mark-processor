#include "../include/mark.h"

int str_to_int(char* str)
{
  if(str[0] == '-'){
    strcpy(str, str+1);
    strcat(str, "-");
  }
  if(str[0] == '+'){
    strcpy(str, str+1);
    strcat(str, "+");
  }
  switch(str[0])
  {
    case 'R':
      switch(str[1])
      {
        case '-':
          return 25;
        case '+':
          return 45;
        default:
          return 35;
      }
    case '1':
      switch(str[1])
      {
        case '-':
          return 52;
        case '+':
          return 58;
        default:
          return 55;
      }
    case '2':
      switch(str[1])
      {
        case '-':
          return 62;
        case '+':
          return 68;
        default:
          return 65;
      }
    case '3':
      switch(str[1])
      {
        case '-':
          return 72;
        case '+':
          return 78;
        default:
          return 75;
      }
    case '4':
      switch(str[1])
      {
        case '-':
          if(str[2] == '-')
            return 80;
          else
            return 85;
        case '+':
          if(str[2] == '+')
            return 100;
          else
            return 95;
        default:
          return 90;
      }
    case '5':
      return 100;
    default:
      return -1000000;
  }
}

char* int_to_str(int mark)
{
  vector<int> marks;
  vector<char*> strings;
  char initials[5] = { 'R', '1', '2', '3', '4' };
  for(int i=0; i<5; i++)
  {
    char *buf = new char[10];
    char *new_str;

    sprintf(buf, "%c", initials[i]);
    marks.push_back(str_to_int(buf));
    new_str = new char[10];
    strings.push_back(new_str);
    strcpy(new_str, buf);

    sprintf(buf, "%c+", initials[i]);
    marks.push_back(str_to_int(buf));
    new_str = new char[10];
    strings.push_back(new_str);
    strcpy(new_str, buf);

    sprintf(buf, "%c++", initials[i]);
    marks.push_back(str_to_int(buf));
    new_str = new char[10];
    strings.push_back(new_str);
    strcpy(new_str, buf);

    sprintf(buf, "%c-", initials[i]);
    marks.push_back(str_to_int(buf));
    new_str = new char[10];
    strings.push_back(new_str);
    strcpy(new_str, buf);

    sprintf(buf, "%c--", initials[i]);
    marks.push_back(str_to_int(buf));
    new_str = new char[10];
    strings.push_back(new_str);
    strcpy(new_str, buf);
  }

  int size = marks.size();

  int closest_value = 100;
  int i_closest = -1;

  for(int i = 0; i < size; i++)
  {
    if(abs(marks[i] - mark) < closest_value)
    {
      i_closest = i;
      closest_value = abs(marks[i] - mark);
    }
  }

  return strings.at(i_closest);
}

Mark::Mark()
{
  _str = 0;
  _int = 0;
}

Mark::Mark(int int_mark)
{
  _int = int_mark;
  _str = int_to_str(int_mark);
}

Mark::Mark(char* str)
{
  _int = str_to_int(str);
  _str = new char[10];
  strncpy(_str, str, 10);
}

char* Mark::to_string()
{
  return _str;
}

int Mark::to_int()
{
  return _int;
}
