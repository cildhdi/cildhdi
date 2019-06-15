#pragma once

#include <json/json.hpp>

#define KEY(type, name, defalut_value) \
    type name = defalut_value;         \
    const char *name##_key = #name;

#define KEY_WD(type, name) \
    type name;             \
    const char *name##_key = #name;
