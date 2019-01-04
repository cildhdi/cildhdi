#pragma once
#include "../storage/Student.h"
#include "../storage/Teacher.h"
#include "../storage/Course.h"
#include "../storage/Storage.h"
#include "../privilege/Modifiable.h"
#include "../privilege/Readable.h"
#include "../privilege/SelfReadable.h"
namespace ea
{

class TeacherUser
    : virtual public SelfReadable<Teacher>,
      virtual public Readable<Student>,
      virtual public Modifiable<Student>,
      virtual public Readable<Course>,
      virtual public Modifiable<Course>
{
  public:
    TeacherUser(Teacher &teacher, std::vector<Student> &students, std::vector<Course> &courses)
        : SelfReadable<Teacher>(teacher),
          Readable<Student>(students),
          Modifiable<Student>(students),
          Readable<Course>(courses),
          Modifiable<Course>(courses)
    {
        Privilege::set_owner("教师");
    }
};

} // namespace ea