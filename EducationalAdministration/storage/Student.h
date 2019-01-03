#pragma once

#include "StorageItem.h"
#include "Course.h"
#include <vector>

namespace ea
{
class Student : public StorageItem
{
  private:
    std::string _name;
    std::string _id;
    std::string _major;
    std::vector<Course> _courses;

  public:
    virtual void output(std::ostream &os)
    {
        os << _name << ' ' << _id << ' ' << _major << ' ' << _courses.size() << std::endl;
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
    static const char *const file_name()
    {
        return "_student.txt";
    }
};
} // namespace ea