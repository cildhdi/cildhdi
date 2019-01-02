#pragma once

#include <iostream>

namespace ea
{
class StorageItem
{
public:
  virtual void output(std::ostream &os) = 0;
  virtual void input(std::istream &is) = 0;
  static const char *const file_name() { return nullptr; }
};
} // namespace ea