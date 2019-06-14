#include <doctest/doctest.h>

#include <account.hpp>

TEST_CASE("Account")
{
    SUBCASE("Constructor")
    {
        {
            ba::Account account;

            CHECK_EQ(account.GetUserName(), "");
            CHECK_EQ(account.GetAccountType(), ba::AccountType::kDebit);
            CHECK_EQ(account.GetRate(), 0.0);
            CHECK_EQ(account.GetLimit(), 0.0);
            CHECK_EQ(account.GetBalance(), 0.0);
        }

        {
            ba::Account account("User", ba::AccountType::kCredit, 0.05, 0.06);

            CHECK_EQ(account.GetUserName(), "User");
            CHECK_EQ(account.GetAccountType(), ba::AccountType::kCredit);
            CHECK_EQ(account.GetRate(), 0.05);
            CHECK_EQ(account.GetLimit(), 0.06);
            CHECK_EQ(account.GetBalance(), 0.0);
        }
    }

    SUBCASE("DebitAccount")
    {
        ba::Account account("User", ba::AccountType::kDebit, 0.1, 0);

        CHECK_EQ(account.GetUserName(), "User");
        CHECK_EQ(account.GetAccountType(), ba::AccountType::kDebit);
        CHECK_EQ(account.GetRate(), 0.1);
        CHECK_EQ(account.GetLimit(), 0);
        CHECK_EQ(account.GetBalance(), 0.0);

        SUBCASE("Deposit")
        {
            account.time = []() {
                return 0;
            };
            auto r = account.Deposit(100.0, "Deposit");
            CHECK(r.success);
            CHECK_EQ(account.GetBalance(), 100.0);

            account.time = []() {
                return ba::kOneDay;
            };
            r = account.Deposit(100.0, "Deposit");
            CHECK(r.success);
            CHECK_EQ(account.GetBalance(), 100 + 100 * 0.1 + 100);

            account.time = []() {
                return ba::kOneDay * 3;
            };
            r = account.Deposit(100.0, "Deposit");
            CHECK(r.success);
            CHECK_EQ(account.GetBalance(), 210 + 210.0 * 0.1 * 2 + 100);

            r = account.Deposit(-100.0, "Deposit");
            CHECK(!r.success);
            CHECK_EQ(account.GetBalance(), 210 + 210.0 * 0.1 * 2 + 100);
        }

        SUBCASE("Withdraw")
        {
            account.time = []() {
                return 0;
            };
            auto r = account.Deposit(100.0, "Deposit");
            CHECK(r.success);
            CHECK_EQ(account.GetBalance(), 100.0);

            account.time = []() {
                return ba::kOneDay;
            };
            r = account.Withdraw(100.0, "Withdraw");
            CHECK(r.success);
            CHECK_EQ(account.GetBalance(), 100.0 * 0.1);

            r = account.Withdraw(100.0, "Withdraw");
            CHECK(!r.success);
            CHECK_EQ(account.GetBalance(), 100.0 * 0.1);

            r = account.Withdraw(-100.0, "Withdraw");
            CHECK(!r.success);
            CHECK_EQ(account.GetBalance(), 100.0 * 0.1);
        }
    }
}