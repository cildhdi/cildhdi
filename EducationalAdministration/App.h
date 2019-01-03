#pragma once

#include "storage/Student.h"
#include "storage/Teacher.h"
#include "storage/Course.h"
#include "storage/Storage.h"

namespace ea
{

class App
{
private:
  Storage<Student> _students;
  Storage<Teacher> _teachers;
  Storage<Course> _courses;

public:
  int run()
  {
    _teachers.save();
    _students.save();
    _courses.save();
    return 0;
  }
};

} // namespace ea