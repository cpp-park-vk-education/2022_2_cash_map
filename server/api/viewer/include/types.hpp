#ifndef WATCH_UP_PROJECT_TYPES_HPP
#define WATCH_UP_PROJECT_TYPES_HPP

#include "nlohmann/json.hpp"

enum type {
    invalid = -1,
    create = 0,
    join,
    leave,
    ping,
    pong,
    play,
    pause_,
    s_time,
    s_nick,
    sync_,
    s_src,
    s_access,

};

static std::unordered_map<std::string, type> const types = {
        {"invalid", type::invalid},
        {"create",  type::create },
        {"join",    type::join   }
};

NLOHMANN_JSON_SERIALIZE_ENUM(type, {
    {invalid, nullptr},
    {create, "create"},
    {join, "join"}
})


#endif //WATCH_UP_PROJECT_TYPES_HPP
