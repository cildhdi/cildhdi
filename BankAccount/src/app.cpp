#include <app.hpp>

namespace ba
{

Options AccountOptions(Account &account, bool &run)
{
    Options options;
    options.AddOption(
        {"存款",
         [&]() {
             auto r = account.Deposit(input<double>("金额"), "存款");
             if (r.success)
                 std::cout << "成功" << std::endl;
             else
                 std::cout << "失败:" << r.detail << std::endl;
         }});

    options.AddOption(
        {"取款",
         [&]() {
             auto r = account.Deposit(input<double>("金额"), "取款");
             if (r.success)
                 std::cout << "成功" << std::endl;
             else
                 std::cout << "失败:" << r.detail << std::endl;
         }});

    options.AddOption(
        {"查看存取记录",
         [&]() {
             account.ShowChanges();
         }});
    options.AddOption(
        {"退出账户",
         [&]() {
             run = false;
         }});
}

App::App(const std::string &file)
    : _file(file)
{
    if (_file.empty())
        return;
}

void App::UpdateOptions()
{
    _options.Clear();
    for (auto &account : _accounts)
    {
        _options.AddOption(
            {"进入账户：" + account.GetUserName(),
             [&]() {
                 std::cout << "账户名：" << account.GetUserName() << std::endl
                           << "账户类型：" << (account.GetAccountType() == kDebit ? "储蓄账户" : "信用账户") << std::endl
                           << "账户余额：" << account.GetBalance() << std::endl
                           << "利率：" << account.GetRate() << std::endl;
                 if (account.GetAccountType() == kCredit)
                     std::cout << "信用额度" << std::endl;
                 bool run = true;
                 AccountOptions(account, run).Run(run);
             }});
    }
    _options.AddOption(
        {"添加账户",
         [&]() {
             std::string username = input<std::string>("账户名");
             double rate = input<double>("利率", [](double r) {
                 return r >= 0 && r <= 1;
             });
             AccountType type = static_cast<AccountType>(
                 input<int>("账户类型(0为储蓄账户，1为信用账户)", [](int t) {
                     return t == 0 || t == 1;
                 }));
             double limit = 0;
             if (type == kCredit)
                 limit = input<double>("信用额度", [](double l) {
                     return l >= 0;
                 });
             AddAccount(Account(username, type, rate, limit));
             UpdateOptions();
         }});
}

std::string App::GetFileName() const
{
    return _file;
}

void App::AddAccount(const Account &account)
{
    _accounts.push_back(account);
}

int App::Run()
{
    bool run = true;
    return _options.Run(run);
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