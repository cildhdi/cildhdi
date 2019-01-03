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
        Privilege::set_owner("ѧ��");
        register_privilege({std::string("ѡ��γ�"), [&]() {
                                std::cout << "\n������γ̱��:\n";
                                std::string id;
                                std::cin >> id;
                                auto it = std::find_if(courses.begin(), courses.end(), [&](StorageItem &course) {
                                    return course == id;
                                });
                                if (it == courses.end())
                                {
                                    std::cout << "δ�ҵ��ÿγ���Ϣ\n";
                                }
                                else
                                {
                                    std::cout << "��ѡ�����¿γ̣�\n";
                                    it->show_head(std::cout);
                                    it->output(std::cout);
                                }
                            }});
    }
};

} // namespace ea