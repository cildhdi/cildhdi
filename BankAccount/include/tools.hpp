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
    std::cout << "请输入" << description << ":\n";
    while (!(std::cin >> data) || !validate(data))
    {
        std::cin.clear();
        std::cin.sync();
        std::cout << "读入" << description << "失败或不符合要求，请重新输入:\n";
    }
    return data;
}

} // namespace ba
