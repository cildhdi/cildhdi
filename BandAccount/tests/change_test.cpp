#include <doctest/doctest.h>
#include <json/json.hpp>

#include <change.hpp>

TEST_CASE("Change")
{
    SUBCASE("ConstructorTest")
    {
        ba::Change change;
        CHECK_EQ(change.time, 0);
        CHECK_EQ(change.change, 0.0);
        CHECK_EQ(change.detail, "");
        CHECK_EQ(change.balance, 0.0);
    }

    SUBCASE("FromJsonTest")
    {
        nlohmann::json json = R"(
            {
                "time": 123,
                "change": 10.0,
                "detail": "利息",
                "balance": 56.8
            }
        )"_json;
        ba::Change change;
        change.FromJson(json);

        CHECK_EQ(change.time, 123);
        CHECK_EQ(change.change, 10.0);
        CHECK_EQ(change.detail, "利息");
        CHECK_EQ(change.balance, 56.8);
    }

    SUBCASE("ToJsonTest")
    {
        ba::Change change;
        change.time = 123;
        change.change = 10.0;
        change.detail = "利息";
        change.balance = 56.8;
        auto json = change.ToJson();

        REQUIRE(json.contains(change.time_key));
        CHECK_EQ(json[change.time_key], 123);

        REQUIRE(json.contains(change.change_key));
        CHECK_EQ(json[change.change_key], 10.0);

        REQUIRE(json.contains(change.detail_key));
        CHECK_EQ(json[change.detail_key], "利息");

        REQUIRE(json.contains(change.balance_key));
        CHECK_EQ(json[change.balance_key], 56.8);
    }
}
