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
    }
    static const char *const file_name()
    {
        return "/files/teacher.txt";
    }
};
} // namespace ea