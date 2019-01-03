#pragma once
#include "Privilege.h"

namespace ea
{

template <typename Item>
class Readable : virtual public Privilege
{
  private:
    std::vector<Item> &_items;

  public:
    Readable(std::vector<Item> &items) : _items(items)
    {
        register_privilege({std::string("�鿴����") + Item::name(), [&]() {
                                if (_items.empty())
                                {
                                    std::cout << "δ�ҵ�" << Item::name() << std::endl;
                                }
                                else
                                {
                                    _items.front().show_head(std::cout);
                                    for (auto &item : _items)
                                        item.output(std::cout);
                                }
                            }});
        register_privilege({std::string("����") + Item::name(), [&]() {
                                std::cout << "������" << Item::name() << "���:\n";
                                std::string id;
                                std::cin >> id;
                                auto it = std::find_if(_items.begin(), items.end(), [&](Item &item) {
                                    return item == id;
                                });
                                if (it == _items.end())
                                {
                                    std::cout << "�����ڸ�" << Item::name() << std::endl;
                                }
                                else
                                {
                                    it->show_head(std::cout);
                                    it->output(std::cout);
                                }
                            }});
    }
};

} // namespace ea
