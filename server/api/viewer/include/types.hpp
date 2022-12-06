#ifndef WATCH_UP_PROJECT_TYPES_HPP
#define WATCH_UP_PROJECT_TYPES_HPP

#include "nlohmann/json.hpp"

enum type {
    invalid = -1,
    create = 0,
    join,
};

NLOHMANN_JSON_SERIALIZE_ENUM(type, {
    {invalid, nullptr},
    {create, "create"},
    {join, "join"}
})


#endif //WATCH_UP_PROJECT_TYPES_HPP
