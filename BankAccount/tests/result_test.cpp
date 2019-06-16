#include <doctest/doctest.h>

#include <result.hpp>

TEST_CASE("Result")
{
    {
        auto r = ba::Result();
        CHECK(r.success);
    }

    {
        auto r = ba::Result{true, "success"};
        CHECK(r.success);
    }

    {
        auto r = ba::Result{false, "error"};
        CHECK(!r.success);
    }
}