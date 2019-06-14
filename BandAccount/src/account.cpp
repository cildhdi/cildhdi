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
        return Result{false, "Must be a positive number"};
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
        return Result{false, "Must be a positive number"};
    CalculateInterest();
    double balance = GetBalance();
    Change change;
    change.time = this->time();
    if (_account_type == AccountType::kDebit)
    {
        if (balance < money)
            return Result{false, "Lack of balance"};
    }
    else
    {
        if (balance + _limit < money)
            return Result{false, "Lack of credit"};
    }
    change.change = -money;
    change.detail = detail;
    change.balance = balance + change.change;
    _changes.push_back(change);
    return Result();
}
} // namespace ba