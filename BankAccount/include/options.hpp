#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <tools.hpp>

namespace ba
{
class Options
{
public:
    using Option = std::pair<std::string, std::function<void(void)>>;

private:
    std::vector<Option> _options;

public:
    void AddOption(Option option)
    {
        _options.push_back(option);
    }

    void ShowOptions() const
    {
        for (size_t i = 0; i < _options.size(); i++)
            std::cout << i << ". " << _options[i].first << std::endl;
    }

    bool ChooseOption(size_t index) const
    {
        if (index >= _options.size())
            return false;
        _options[index].second();
        return true;
    }

    int Run(bool &run)
    {
        std::cout << "可用选项：\n";
        ShowOptions();
        while (run)
            ChooseOption(input<size_t>("序号"));
        return 0;
    }

    void Clear()
    {
        _options.clear();
    }
};
} // namespace ba
