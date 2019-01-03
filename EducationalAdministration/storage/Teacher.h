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
        os << std::setw(10) << "����" << std::setw(10) << "��ʦ���" << std::setw(15) << "רҵ" << std::setw(15) << "ְ��" << std::endl;
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
        util::modify("��ʦ����", _name);
        util::modify("��ʦ���", _id);
        util::modify("רҵ", _major);
        util::modify("ְ��", _job);
    }

    static const char *const file_name()
    {
        return "_teacher.txt";
    }

    static const char *const name()
    {
        return "��ʦ";
    }
};
} // namespace ea