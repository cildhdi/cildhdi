#pragma once

#include "StorageItem.h"

namespace ea
{
class Course : public StorageItem
{
  private:
    std::string _id;
    std::string _name;
    double _credit;

  public:
    virtual void output(std::ostream &os)
    {
        os << _id << ' ' << _name << ' ' << _credit << std::endl;
    }
    virtual void input(std::istream &is)
    {
        is >> _id >> _name >> _credit;
        valid_check(is);
    }
    static const char *const file_name()
    {
        return "_course.txt";
    }
};
} // namespace ea