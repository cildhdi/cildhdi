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
    std::cout << "������" << descrption << ":\n";
    while (!(std::cin >> data))
    {
        std::cin.clear();
        std::cin.sync();
        std::cout << "����" << descrption << "ʧ�ܣ�����������:\n";
    }
    std::cout << "����ɹ�!\n\n";
}
} // namespace util

} // namespace ea