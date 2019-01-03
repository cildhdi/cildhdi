#pragma once

#include "Privilege.h"

namespace ea
{

template <typename Item>
class SelfReadable : virtual public Privilege
{
  private:
    Item &_item;

  public:
    SelfReadable(Item &item) : _item(item)
    {
        register_privilege({std::string("查看本人信息"), [&]() {
                                _item.show_head(std::cout);
                                _item.output(std::cout);
                            }});
    }
};

} //namespace ea