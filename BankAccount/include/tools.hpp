#pragma once

#include <string>
#include <functional>

namespace ba
{

template <typename T>
T input(const std::string &description, std::function<bool(T)> validate = [](T t) {
    return true;
})
{
    T data;
    std::cout << "������" << description << ":\n";
    while (!(std::cin >> data) || !validate(data))
    {
        std::cin.clear();
        std::cin.sync();
        std::cout << "����" << description << "ʧ�ܻ򲻷���Ҫ������������:\n";
    }
    return data;
}

} // namespace ba
