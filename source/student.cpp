#include "../include/student.h"

Mark Student::final_mark()
{
  float term_mark = this->term_mark().to_int();
  float exam_mark = this->exam_mark().to_int();
  float summative_mark = this->summative_mark().to_int();

  float final = term_mark * 0.7f + exam_mark * 0.2f + summative_mark * 0.1f;
  return Mark(int(final + 0.5f));
}

Mark Student::final_mark(int units)
{
  float term_mark = this->term_mark(units).to_int();
  float exam_mark = this->exam_mark().to_int();
  float summative_mark = this->summative_mark().to_int();

  float final = term_mark * 0.7f + exam_mark * 0.2f + summative_mark * 0.1f;
  return Mark(int(final + 0.5f));
}

Mark Student::term_mark()
{
  int n_oas = OAs.size();
  float term_mark = 0.0f;
  if(n_oas > 0)
  {
    for(int i=0; i < n_oas; i++)
    {
      term_mark += float(OAs.at(i).to_int());
    }
    term_mark /= n_oas;
  }
  return Mark(int(term_mark + 0.5f));
}

Mark Student::term_mark(int units)
{
  int max_oas = OAs.size();
  float term_mark = 0.0f;
  for(int i=0; i<units && i<max_oas; i++)
  {
    term_mark += float(OAs.at(i).to_int());
  }
  if(units > max_oas)
  {
    if(max_oas > 0)
      return Mark(int(term_mark/float(max_oas) + 0.5f));
    else
      return Mark(0);
  }
  if(units > 0)
    return Mark(int(term_mark/float(units) + 0.5f));
  else
    return Mark(0);
}

Mark Student::exam_mark()
{
  float exam_mark = 0.0f;
  int n_exams = Exams.size();
  if(n_exams > 0)
  {
    int exams_present = 0;
    for(int i=0; i < n_exams; i++)
    {
      if(Exams.at(i).to_int() >= 0)
      {
        exam_mark += float(Exams.at(i).to_int());
        exams_present++;
      }
    }
    if(exams_present > 0)
      exam_mark /= float(exams_present);
    else
      exam_mark = 0;
  }
  return Mark(int(exam_mark + 0.5f));
}

Mark Student::summative_mark()
{
  float summative_mark = 0.0f;
  int n_summatives = Summatives.size();
  if(n_summatives > 0)
  {
    int summatives_present = 0;
    for(int i=0; i < n_summatives; i++)
    {
      if(Summatives.at(i).to_int() >= 0)
      {
        summative_mark += float(Summatives.at(i).to_int());
        summatives_present++;
      }
    }
    if(summatives_present > 0)
      summative_mark /= float(summatives_present);
    else
      summative_mark = 0;
  }
  return Mark(int(summative_mark + 0.5f));
}