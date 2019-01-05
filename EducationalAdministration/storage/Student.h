#pragma once

#include "StorageItem.h"
#include "Course.h"
#include <vector>

namespace ea
{

class StudentUser;

class Student : public StorageItem
{
  private:
    std::string _name;
    std::string _major;
    std::vector<Course> _courses;
    friend class StudentUser;
  public:
    virtual void show_head(std::ostream &os)
    {
        os << std::setw(10) << "����" << std::setw(10) << "ѧ��" << std::setw(15) << "רҵ" << std::endl;
    }
    virtual void output(std::ostream &os)
    {
        os << std::setw(10) << _name << std::setw(10) << _id << std::setw(15) << _major << ' ' << _courses.size() << std::endl;
        for (auto &course : _courses)
            course.output(os);
    }
    virtual void input(std::istream &is)
    {
        int size = 0;
        is >> _name >> _id >> _major >> size;
        _courses.clear();
        while (size--)
        {
            Course course;
            course.input(is);
            if (course.valid())
                _courses.push_back(std::move(course));
        }
        valid_check(is);
    }

    virtual void modify()
    {
        util::modify("����", _name);
        util::modify("ѧ��", _id);
        util::modify("רҵ", _major);
    }

    static const char *const file_name()
    {
        return "_student.txt";
    }

    static const char *const name()
    {
        return "ѧ��";
    }
};
} // namespace ea