#pragma once

#include <iostream>
#include <string>

namespace ea
{
class StorageItem
{
private:
  bool _valid = false;

public:
  bool valid() const { return _valid; }
  virtual void output(std::ostream &os) = 0;
  virtual void input(std::istream &is) = 0;
  void valid_check(std::istream &is)
  {
    _valid = !!is;
  }
  static const char *const file_name() { return nullptr; }
};
} // namespace ea