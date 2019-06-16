#include <doctest/doctest.h>
#include <iostream>

#include <app.hpp>

TEST_CASE("App")
{
    SUBCASE("Constructor")
    {
        std::string filename = "";
        ba::App app(filename);

        CHECK_EQ(app.GetFileName(), filename);
    }

    SUBCASE("Json")
    {
        std::string filename = "";
        ba::App app(filename);

        app.AddAccount(ba::Account("User", ba::AccountType::kDebit, 0.1, 0));
        app.AddAccount(ba::Account("User", ba::AccountType::kCredit, 0.1, 100));

        auto json = app.ToJson();
        std::cout << json.dump(4) << std::endl;
        ba::App _app(filename);
        _app.FromJson(json);
    }
}