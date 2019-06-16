#include <app.hpp>

namespace ba
{

Options App::AccountOptions(Account &account, bool &run)
{
    Options options;
    options.AddOption(
        {"�˻���Ϣ", [&]() {
             account.ShowInfo();
         }});
    options.AddOption(
        {"���",
         [&]() {
             auto r = account.Deposit(input<double>("���", [](double m) { return m > 0; }), "deposit");
             if (r.success)
             {
                 std::cout << "�ɹ�" << std::endl;
                 Save();
             }
             else
                 std::cout << "ʧ��:" << r.detail << std::endl;
         }});

    options.AddOption(
        {"ȡ��",
         [&]() {
             auto r = account.Withdraw(input<double>("���", [](double m) { return m > 0; }), "withdraw");
             if (r.success)
             {
                 std::cout << "�ɹ�" << std::endl;
                 Save();
             }
             else
                 std::cout << "ʧ��:" << r.detail << std::endl;
         }});

    options.AddOption(
        {"�鿴��ȡ��¼",
         [&]() {
             account.ShowChanges();
         }});
    options.AddOption(
        {"�˳��˻�",
         [&]() {
             run = false;
         }});
    return options;
}

App::App(const std::string &file)
    : _file(file)
{
    if (!_file.empty())
    {
        std::fstream fs;
        fs.open(_file);
        if (!fs.is_open())
        {
            fs.clear();
            fs.open(_file, std::ios::in);
        }
        nlohmann::json json;
        fs >> json;
        FromJson(json);
        fs.close();
    }
    UpdateOptions();
}

void App::UpdateOptions()
{
    _options.Clear();
    for (auto &account : _accounts)
    {
        _options.AddOption(
            {"�����˻���" + account.GetUserName(),
             [&]() {
                 bool run = true;
                 account.ShowInfo();
                 AccountOptions(account, run).Run(run);
             }});
    }
    _options.AddOption(
        {"����˻�",
         [&]() {
             std::string username = input<std::string>("�˻��������������ģ�");
             double rate = input<double>("����", [](double r) {
                 return r >= 0 && r <= 1;
             });
             AccountType type = static_cast<AccountType>(
                 input<int>("�˻�����(0Ϊ�����˻���1Ϊ�����˻�)", [](int t) {
                     return t == 0 || t == 1;
                 }));
             double limit = 0;
             if (type == kCredit)
                 limit = input<double>("���ö��", [](double l) {
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
    Save();
}

int App::Run()
{
    bool run = true;
    return _options.Run(run);
}

void App::Save() const
{
    if (!_file.empty())
    {
        std::fstream fs;
        fs.open(_file);
        if (!fs.is_open())
        {
            fs.clear();
            fs.open(_file, std::ios::out);
        }
        fs << ToJson().dump(4);
        fs.close();
    }
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