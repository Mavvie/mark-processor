#pragma once

class CSV {
public:
  CSV();
  CSV(const char* lpFn);
  ~CSV();
  bool read(const char* lpFn);
  const char* file_path();
private:
  const char* _file_path;
}