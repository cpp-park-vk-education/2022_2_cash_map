#ifndef WATCH_UP_PROJECT_TYPES_HPP
#define WATCH_UP_PROJECT_TYPES_HPP

#include "nlohmann/json.hpp"

enum class vs_type {
    invalid = -1,
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
    chat,
    s_service,
};

static std::unordered_map<std::string, vs_type> const types = {
        {"invalid",  vs_type::invalid },
        {"leave",    vs_type::leave   },
        {"ping",     vs_type::ping    },
        {"pong",     vs_type::pong    },
        {"play",     vs_type::play    },
        {"pause",    vs_type::pause_  },
        {"s_time",   vs_type::s_time  },
        {"s_nick",   vs_type::s_nick  },
        {"sync",     vs_type::sync_   },
        {"s_src",    vs_type::s_src   },
        {"s_access", vs_type::s_access},
        {"chat",     vs_type::chat    },
        {"s_service",vs_type::s_service}
};

static std::unordered_map<vs_type, std::string> const type_to_string = {
        {vs_type::invalid,  "invalid"  },
        {vs_type::leave,    "leave"   },
        {vs_type::ping,     "ping"    },
        {vs_type::pong,     "pong"    },
        {vs_type::play,     "play"    },
        {vs_type::pause_,   "pause"   },
        {vs_type::s_time,   "s_time"  },
        {vs_type::s_nick,   "s_nick"  },
        {vs_type::sync_ ,   "sync"    },
        {vs_type::s_src ,   "s_src"   },
        {vs_type::s_access, "s_access"},
        {vs_type::chat,      "chat"},
        {vs_type::s_service, "s_service"},
};

NLOHMANN_JSON_SERIALIZE_ENUM(vs_type, {
    {vs_type::invalid,  nullptr   },
    {vs_type::leave,    "leave"   },
    {vs_type::ping,     "ping"    },
    {vs_type::pong,     "pong"    },
    {vs_type::play,     "play"    },
    {vs_type::pause_,   "pause"   },
    {vs_type::s_time,   "s_time"  },
    {vs_type::s_nick,   "s_nick"  },
    {vs_type::sync_,    "sync"    },
    {vs_type::s_src,    "s_src"   },
    {vs_type::s_access, "s_access"},
    {vs_type::chat,      "chat"   },
    {vs_type::s_service, "s_service"},
})


#endif //WATCH_UP_PROJECT_TYPES_HPP
