#include <app.hpp>

namespace ba
{
App::App(const std::string &file)
    : _file(file)
{
    if (_file.empty())
        return;
}

std::string App::GetFileName() const
{
    return _file;
}

void App::AddAccount(const Account &account)
{
    _accounts.push_back(account);
}

nlohmann::json App::ToJson() const
{
    std::vector<nlohmann::json> accounts;
    accounts.reserve(_accounts.size());
    std::for_each(_accounts.begin(), _accounts.end(), [&](const Account &account) {
        accounts.push_back(account.ToJson());
    });
    return {
        {_accounts_key, accounts}};
}

void App::FromJson(nlohmann::json json)
{
    if (json.contains(_accounts_key))
    {
        auto accounts = json[_accounts_key];
        _accounts.clear();
        for (auto &account_json : accounts)
        {
            Account account;
            account.FromJson(account_json);
            _accounts.push_back(account);
        }
    }
}

} // namespace ba