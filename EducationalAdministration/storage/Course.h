#pragma once

#include "StorageItem.h"

namespace ea
{
class Course : public StorageItem
{
  private:
    std::string _name;
    double _credit;

  public:
    virtual void show_head(std::ostream &os)
    {
        os << std::setw(15) << "课程编号" << std::setw(15) << "课程名" << std::setw(5) << "学分" << std::endl;
    }

    virtual void output(std::ostream &os)
    {
        os << std::setw(15) << _id << std::setw(15) << _name << std::setw(5) << _credit << std::endl;
    }

    virtual void input(std::istream &is)
    {
        is >> _id >> _name >> _credit;
        valid_check(is);
    }

    virtual void modify()
    {
        util::modify("编号", _id);
        util::modify("课程名称", _name);
        util::modify("学分", _credit);
    }

    static const char *const file_name()
    {
        return "_course.txt";
    }

    static const char *const name()
    {
        return "课程";
    }
};
} // namespace ea