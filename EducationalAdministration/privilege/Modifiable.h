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
        register_privilege({std::string("增加") + Item::name(), [&]() {
                                Item item;
                                item.modify();
                                _items.push_back(std::move(item));
                                std::cout << "添加成功!";
                            }});
        register_privilege({std::string("删除") + Item::name(), [&]() {
                                std::cout << "请输入" << Item::name() << "编号:\n";
                                std::string id;
                                std::cin >> id;
                                auto it = std::find_if(_items.begin(), items.end(), [&](Item &item) {
                                    return item == id;
                                });
                                if (it == _items.end())
                                {
                                    std::cout << "不存在该" << Item::name() << std::endl;
                                }
                                else
                                {
                                    _items.erase(it);
                                    std::cout << "删除成功！\n";
                                }
                            }});
        register_privilege({std::string("修改") + Item::name(), [&]() {
                                std::cout << "请输入" << Item::name() << "编号:\n";
                                std::string id;
                                std::cin >> id;
                                auto it = std::find_if(_items.begin(), items.end(), [&](Item &item) {
                                    return item == id;
                                });
                                if (it == _items.end())
                                {
                                    std::cout << "不存在该" << Item::name() << std::endl;
                                }
                                else
                                {
                                    it->modify();
                                    std::cout << "修改成功！\n";
                                }
                            }});
    }
};

} // namespace ea
