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
                "教务管理系统\n请输入身份或操作前的字母，或输入其它字符直接退出：\n"
                "a.学生\nb.教师\nc.管理员\nd.保存此次操作并退出\n";

            char ch;
            std::cin >> ch;
            if (!(ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd'))
                return 0;

            Privilege* user = nullptr;
            switch (ch)
            {
            case 'a':
            {
                std::cout << "\n请输入学号:\n";
                std::string id;
                std::cin >> id;
                auto it = std::find_if(_students._items.begin(), _students._items.end(), [&](StorageItem& student)
                {
                    return student == id;
                });
                if (it == _students._items.end())
                {
                    std::cout << "未找到该id信息\n";
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
                std::cout << "\n请输入教师编号:\n";
                std::string id;
                std::cin >> id;
                auto it = std::find_if(_teachers._items.begin(), _teachers._items.end(), [&](StorageItem& teacher)
                {
                    return teacher == id;
                });
                if (it == _teachers._items.end())
                {
                    std::cout << "未找到该id信息\n";
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
                    "您当前以" << user->owner() << "的身份登录，您具有以下权限：\n";
                user->show_privilege();
                std::cout << "请输入要执行的权限前的字母，或输入其它字符直接回到主菜单：\n";
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