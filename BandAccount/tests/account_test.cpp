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
            ba::Account account("用户", ba::AccountType::kCredit, 0.05, 0.06);

            CHECK_EQ(account.GetUserName(), "用户");
            CHECK_EQ(account.GetAccountType(), ba::AccountType::kCredit);
            CHECK_EQ(account.GetRate(), 0.05);
            CHECK_EQ(account.GetLimit(), 0.06);
            CHECK_EQ(account.GetBalance(), 0.0);
        }
    }

    SUBCASE("DebitAccount")
    {
        ba::Account account("用户", ba::AccountType::kCredit, 0.05, 0.06);

        CHECK_EQ(account.GetUserName(), "用户");
        CHECK_EQ(account.GetAccountType(), ba::AccountType::kCredit);
        CHECK_EQ(account.GetRate(), 0.05);
        CHECK_EQ(account.GetLimit(), 0.06);
        CHECK_EQ(account.GetBalance(), 0.0);
    }
}