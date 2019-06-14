#pragma once

#include <storage_object.hpp>

namespace ba
{

struct Change
{
    KEY(time_t, time, 0);
    KEY(double, change, 0.0);
    KEY(std::string, detail, "");
    KEY(double, balance, 0.0);

    nlohmann::json ToJson()
    {
        return {
            {time_key, time},
            {change_key, change},
            {detail_key, detail},
            {balance_key, balance}};
    }

    void FromJson(nlohmann::json json)
    {
        if (json.contains(time_key))
            time = json[time_key];
        if (json.contains(change_key))
            change = json[change_key];
        if (json.contains(detail_key))
            detail = json[detail_key];
        if (json.contains(balance_key))
            balance = json[balance_key];
    }
};

} // namespace ba
