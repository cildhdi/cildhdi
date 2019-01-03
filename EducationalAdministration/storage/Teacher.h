#pragma once

#include "StorageItem.h"

namespace ea
{
class Teacher : public StorageItem
{
  private:
    std::string _name;
    std::string _major;
    std::string _job;

  public:
    virtual void show_head(std::ostream &os)
    {
        os << std::setw(10) << "姓名" << std::setw(10) << "教师编号" << std::setw(15) << "专业" << std::setw(15) << "职称" << std::endl;
    }

    virtual void output(std::ostream &os)
    {
        os << std::setw(10) << _name << std::setw(10) << _id << std::setw(15) << _major << std::setw(15) << _job << std::endl;
    }

    virtual void input(std::istream &is)
    {
        is >> _name >> _id >> _major >> _job;
        valid_check(is);
    }

    virtual void modify()
    {
        util::modify("教师姓名", _name);
        util::modify("教师编号", _id);
        util::modify("专业", _major);
        util::modify("职称", _job);
    }

    static const char *const file_name()
    {
        return "_teacher.txt";
    }

    static const char *const name()
    {
        return "老师";
    }
};
} // namespace ea