#pragma once

#include <vector>
#include <map>
#include <functional>
#include <string>

namespace ea
{
using PrivilegeInfo = std::pair<std::string, std::function<void(void)>>;

class Privilege
{
private:
    std::vector<PrivilegeInfo> _privileges;
    std::string _owner;

public:
    virtual void set_owner(const std::string &owner)
    {
        _owner = owner;
    }

    virtual std::string owner() const
    {
        return _owner;
    }

    virtual void register_privilege(const PrivilegeInfo &privilege_info)
    {
        _privileges.push_back(privilege_info);
    }

    virtual void show_privilege()
    {
        for (unsigned int i = 0; i < _privileges.size(); i++)
            std::cout << static_cast<char>('a' + i) << ". " << _privileges[i].first << std::endl;
    }

    virtual bool run(int ch = 'a')
    {
        if ((ch - 'a') >= 0 && (ch - 'a') < static_cast<int>(_privileges.size()))
        {
            _privileges[ch - 'a'].second();
            return true;
        }
        return false;
    }

    virtual ~Privilege()
    {
    }
};
} // namespace ea