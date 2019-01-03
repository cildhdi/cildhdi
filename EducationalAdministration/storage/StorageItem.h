#pragma once

#include "../util.h"
#include <iostream>
#include <string>
#include <iomanip>

namespace ea
{
class StorageItem
{
  private:
    bool _valid = true;

  protected:
    std::string _id;

  public:
    virtual void show_head(std::ostream &os) = 0;
    virtual void output(std::ostream &os) = 0;
    virtual void input(std::istream &is) = 0;
    virtual void modify() = 0;
    bool valid() const { return _valid; }
    void valid_check(std::istream &is)
    {
        _valid = !!is;
    }
    bool operator==(const std::string &id)
    {
        return _id == id;
    }
    static const char *const file_name() { return nullptr; }
    static const char *const name() { return nullptr; }
};
} // namespace ea