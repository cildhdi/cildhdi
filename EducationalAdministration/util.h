#pragma once
#include <string>
#include <iostream>

namespace ea
{

namespace util
{
template <typename T>
void modify(const std::string &descrption, T &data)
{
    std::cout << "请输入" << descrption << ":\n";
    while (!(std::cin >> data))
    {
        std::cin.clear();
        std::cin.sync();
        std::cout << "读入" << descrption << "失败，请重新输入:\n";
    }
    std::cout << "读入成功!\n\n";
}
} // namespace util

} // namespace ea