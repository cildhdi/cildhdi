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

class StudentUser
    : virtual public SelfReadable<Student>,
      virtual public Readable<Course>
{
  public:
    StudentUser(Student &student, std::vector<Course> &courses)
        : SelfReadable<Student>(student),
          Readable<Course>(courses)
    {
        Privilege::set_owner("学生");
        register_privilege({std::string("选择课程"), [&]() {
                                std::cout << "\n请输入课程编号:\n";
                                std::string id;
                                std::cin >> id;
                                auto it = std::find_if(courses.begin(), courses.end(), [&](StorageItem &course) {
                                    return course == id;
                                });
                                if (it == courses.end())
                                {
                                    std::cout << "未找到该课程信息\n";
                                }
                                else
                                {
                                    student._courses.push_back(*it);
                                    std::cout << "已选入以下课程：\n";
                                    it->show_head(std::cout);
                                    it->output(std::cout);
                                }
                            }});
    }
};

} // namespace ea