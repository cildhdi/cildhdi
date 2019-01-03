#pragma once
#include "Privilege.h"
#include <algorithm>

namespace ea
{

template <typename Item>
class Modifiable : virtual public Privilege
{
  private:
    std::vector<Item> &_items;

  public:
    Modifiable(std::vector<Item> &items) : _items(items)
    {
        register_privilege({std::string("����") + Item::name(), [&]() {
                                Item item;
                                item.modify();
                                _items.push_back(std::move(item));
                                std::cout << "��ӳɹ�!";
                            }});
        register_privilege({std::string("ɾ��") + Item::name(), [&]() {
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
                                    _items.erase(it);
                                    std::cout << "ɾ���ɹ���\n";
                                }
                            }});
        register_privilege({std::string("�޸�") + Item::name(), [&]() {
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
                                    it->modify();
                                    std::cout << "�޸ĳɹ���\n";
                                }
                            }});
    }
};

} // namespace ea
