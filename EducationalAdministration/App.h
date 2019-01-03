#pragma once

#include "storage/Student.h"
#include "storage/Teacher.h"
#include "storage/Course.h"
#include "storage/Storage.h"

#include "user/AdminUser.h"
#include "user/TeacherUser.h"
#include "user/StudentUser.h"

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
        while (true)
        {
            std::cout << "\n\n-------------------------------------------------\n"
                "�������ϵͳ\n��������ݻ����ǰ����ĸ�������������ַ�ֱ���˳���\n"
                "a.ѧ��\nb.��ʦ\nc.����Ա\nd.����˴β������˳�\n";

            char ch;
            std::cin >> ch;
            if (!(ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd'))
                return 0;

            Privilege* user = nullptr;
            switch (ch)
            {
            case 'a':
            {
                std::cout << "\n������ѧ��:\n";
                std::string id;
                std::cin >> id;
                auto it = std::find_if(_students._items.begin(), _students._items.end(), [&](StorageItem& student)
                {
                    return student == id;
                });
                if (it == _students._items.end())
                {
                    std::cout << "δ�ҵ���id��Ϣ\n";
                    continue;
                }
                else
                {
                    user = new StudentUser(*it, _courses._items);
                }
                break;
            }
            case 'b':
            {
                std::cout << "\n�������ʦ���:\n";
                std::string id;
                std::cin >> id;
                auto it = std::find_if(_teachers._items.begin(), _teachers._items.end(), [&](StorageItem& teacher)
                {
                    return teacher == id;
                });
                if (it == _teachers._items.end())
                {
                    std::cout << "δ�ҵ���id��Ϣ\n";
                    continue;
                }
                else
                {
                    user = new TeacherUser(*it, _students._items, _courses._items);
                }
                break;
            }
            case 'c':
            {
                user = new AdminUser(_students._items, _courses._items, _teachers._items);
                break;
            }
            case 'd':
            {
                _students.save();
                _teachers.save();
                _courses.save();
                return 0;
            }
            default:
                return 0;
            }
            do
            {
                std::cout << "\n-------------------------\n"
                    "����ǰ��" << user->owner() << "����ݵ�¼������������Ȩ�ޣ�\n";
                user->show_privilege();
                std::cout << "������Ҫִ�е�Ȩ��ǰ����ĸ�������������ַ�ֱ�ӻص����˵���\n";
                std::cin >> ch;
                std::cin.clear();
                std::cin.sync();
            } while (user->run(ch));

            if (user)
            {
                delete user;
                user = nullptr;
            };
        }
        return 0;
    }
};

} // namespace ea