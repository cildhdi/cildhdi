#pragma once

#include "StorageItem.h"
#include <vector>
#include <fstream>

namespace ea
{
template <typename Item>
class Storage
{
public:
    std::vector<Item> _items;

public:
    Storage()
    {
        std::ifstream ifs(Item::file_name());
        if (ifs.is_open())
        {
            while (!ifs.eof())
            {
                Item item;
                item.input(ifs);
                if (item.valid())
                    _items.push_back(std::move(item));
                else
                    break;
            }
            ifs.close();
        }
    }

    void save()
    {
        std::ofstream ofs(Item::file_name());
        if (ofs.is_open())
            for (auto &item : _items)
                item.output(ofs);
        ofs.close();
    }
};
} // namespace ea