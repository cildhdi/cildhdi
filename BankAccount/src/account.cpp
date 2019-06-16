#include <account.hpp>

namespace ba
{

void Account::CalculateInterest()
{
    if (_changes.empty())
        return;
    Change change;
    auto &latest_change = _changes.back();
    time_t now = this->time();
    int days = (now - latest_change.time) / kOneDay;
    change.time = now;
    change.change = (_account_type == AccountType::kCredit && latest_change.balance > 0.0)
                        ? 0.0
                        : latest_change.balance * days * _rate;
    change.detail = "interest";
    change.balance = latest_change.balance + change.change;
    _changes.push_back(change);
}

std::string Account::GetUserName() const
{
    return this->_user_name;
}

AccountType Account::GetAccountType() const
{
    return this->_account_type;
}

double Account::GetRate() const
{
    return this->_rate;
}

double Account::GetLimit() const
{
    return this->_limit;
}

double Account::GetBalance() const
{
    return _changes.empty() ? 0.0 : _changes.back().balance;
}

Result Account::Deposit(double money, const std::string &detail)
{
    if (money <= 0)
        return Result{false, "必须为正数"};
    CalculateInterest();
    Change change;
    change.time = this->time();
    change.change = money;
    change.detail = detail;
    change.balance = GetBalance() + money;
    _changes.push_back(change);
    return Result();
}

Result Account::Withdraw(double money, const std::string &detail)
{
    if (money <= 0)
        return Result{false, "必须为正数"};
    CalculateInterest();
    double balance = GetBalance();
    Change change;
    change.time = this->time();
    if (_account_type == AccountType::kDebit)
    {
        if (balance < money)
            return Result{false, "余额不足"};
    }
    else
    {
        if (balance + _limit < money)
            return Result{false, "额度不足"};
    }
    change.change = -money;
    change.detail = detail;
    change.balance = balance + change.change;
    _changes.push_back(change);
    return Result();
}

nlohmann::json Account::ToJson() const
{
    std::vector<nlohmann::json> changes;
    changes.reserve(_changes.size());
    std::for_each(_changes.begin(), _changes.end(), [&](const Change &change) {
        changes.push_back(change.ToJson());
    });
    return {
        {_user_name_key, _user_name},
        {_account_type_key, static_cast<int>(_account_type)},
        {_rate_key, _rate},
        {_limit_key, _limit},
        {_changes_key, changes}};
}
void Account::FromJson(nlohmann::json json)
{
    if (json.contains(_user_name_key))
        _user_name = json[_user_name_key];
    if (json.contains(_account_type_key))
        _account_type = static_cast<AccountType>(
            static_cast<int>(json[_account_type_key]));
    if (json.contains(_rate_key))
        _rate = json[_rate_key];
    if (json.contains(_limit_key))
        _limit = json[_limit_key];
    if (json.contains(_changes_key))
    {
        auto changes = json[_changes_key];
        _changes.clear();
        for (auto &change_json : changes)
        {
            Change change;
            change.FromJson(change_json);
            _changes.push_back(change);
        }
        std::sort(_changes.begin(), _changes.end(), [](Change &l, Change &r) {
            return l.time < r.time;
        });
    }
}

void Account::ShowChanges() const
{
    std::cout << std::setw(30) << "时间" << std::setw(20) << "金额变化"
              << std::setw(10) << "余额"
              << std::setw(20) << "详细信息" << std::endl;
    std::cout << "================================================================================" << std::endl;
    for (auto it = _changes.rbegin(); it != _changes.rend(); ++it)
    {
        std::string time_str = std::asctime(std::localtime(&it->time));
        std::cout << std::setw(30) << time_str.substr(0, time_str.size() - 1)
                  << std::setw(20) << (it->change > 0 ? ("+" + std::to_string(it->change)) : std::to_string(it->change)) << std::setw(10)
                  << it->balance << std::setw(20) << it->detail << std::endl;
    }
}

void Account::ShowInfo() const
{
    std::cout << "账户名：" << GetUserName() << std::endl
              << "账户类型：" << (GetAccountType() == kDebit ? "储蓄账户" : "信用账户") << std::endl
              << "账户余额：" << GetBalance() << std::endl
              << "利率：" << GetRate() << std::endl;
    if (GetAccountType() == kCredit)
        std::cout << "信用额度" << GetLimit() << std::endl;
}

} // namespace ba