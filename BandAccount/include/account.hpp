#pragma once

#include <string>
#include <vector>
#include <functional>
#include <ctime>
#include <json/json.hpp>
#include <algorithm>

#include <result.hpp>
#include <storage_object.hpp>
#include <change.hpp>

namespace ba
{

const int kOneDay = (24 * 60 * 60);

enum AccountType
{
    kDebit = 0,
    kCredit = 1
};

class Account
{
private:
    KEY(std::string, _user_name, "");
    KEY(AccountType, _account_type, AccountType::kDebit);
    KEY(double, _rate, 0.0);
    KEY(double, _limit, 0.0);
    KEY_WD(std::vector<Change>, _changes);

private:
    void CalculateInterest();

public:
    std::function<time_t()> time = []() -> time_t {
        return std::time(nullptr);
    };

    nlohmann::json ToJson() const;
    void FromJson(nlohmann::json json);

public:
    Account(const std::string &user_name = "", AccountType account_type = AccountType::kDebit,
            double rate = 0.0, double limit = 0.0)
        : _user_name(user_name),
          _account_type(account_type),
          _rate(rate),
          _limit(limit) {}
    std::string GetUserName() const;
    AccountType GetAccountType() const;
    double GetRate() const;
    double GetBalance() const;
    double GetLimit() const;
    Result Deposit(double money, const std::string &detail);
    Result Withdraw(double money, const std::string &detail);
};

} // namespace ba
