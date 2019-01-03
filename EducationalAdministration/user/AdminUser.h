#pragma once
#include "../storage/Student.h"
#include "../storage/Teacher.h"
#include "../storage/Course.h"
#include "../storage/Storage.h"

#include "../privilege/Modifiable.h"
#include "../privilege/Readable.h"

namespace ea
{

class AdminUser :
    virtual public Readable<Student>, virtual public Modifiable<Student>,
    virtual public Readable<Course>, virtual public Modifiable<Course>,
    virtual public Readable<Teacher>, virtual public Modifiable<Teacher>
{
public:
    AdminUser(std::vector<Student>& students, std::vector<Course>& courses, std::vector<Teacher>& teachers) :
        Readable<Student>(students), Modifiable<Student>(students),
        Readable<Course>(courses), Modifiable<Course>(courses),
        Readable<Teacher>(teachers), Modifiable<Teacher>(teachers)
    {
        Privilege::set_owner("π‹¿Ì‘±");
    }
};

} // namespace ea