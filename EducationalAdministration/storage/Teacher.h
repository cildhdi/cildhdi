#pragma once

#include "StorageItem.h"

namespace ea
{
class Teacher : public StorageItem
{
  private:
    std::string _name;
    std::string _id;

  public:
    virtual void output(std::ostream &os)
    {
        os << _name << ' ' << _id << std::endl;
    }
    virtual void input(std::istream &is)
    {
        is >> _name >> _id;
        valid_check(is);
    }
    static const char *const file_name()
    {
        return "_teacher.txt";
    }
};
} // namespace ea