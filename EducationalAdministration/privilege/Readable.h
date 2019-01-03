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
        register_privilege({std::string("查看所有") + Item::name(), [&]() {
                                if (_items.empty())
                                {
                                    std::cout << "未找到" << Item::name() << std::endl;
                                }
                                else
                                {
                                    _items.front().show_head(std::cout);
                                    for (auto &item : _items)
                                        item.output(std::cout);
                                }
                            }});
        register_privilege({std::string("查找") + Item::name(), [&]() {
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
                                    it->show_head(std::cout);
                                    it->output(std::cout);
                                }
                            }});
    }
};

} // namespace ea
