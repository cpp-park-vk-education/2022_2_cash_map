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
        {"invalid", type::invalid },
        {"create",  type::create  },
        {"join",    type::join    },
        {"leave",   type::leave   },
        {"ping",    type::ping    },
        {"pong",    type::pong    },
        {"play",    type::play    },
        {"pause",   type::pause_  },
        {"s_time",  type::s_time  },
        {"s_nick",  type::s_nick  },
        {"sync",    type::sync_   },
        {"s_src",   type::s_src   },
        {"s_access",type::s_access},
};

static std::unordered_map<type, std::string> const type_to_string = {
        {type::invalid, "invalid"  },
        {type::create,   "create"  },
        {type::join ,    "join"    },
        {type::leave,    "leave"   },
        {type::ping,     "ping"    },
        {type::pong,     "pong"    },
        {type::play,     "play"    },
        {type::pause_,   "pause"   },
        {type::s_time,   "s_time"  },
        {type::s_nick,   "s_nick"  },
        {type::sync_ ,   "sync"    },
        {type::s_src ,   "s_src"   },
        {type::s_access, "s_access"},
};

NLOHMANN_JSON_SERIALIZE_ENUM(type, {
    {invalid,  nullptr   },
    {create,   "create"  },
    {join,     "join"    },
    {leave,    "leave"   },
    {ping,     "ping"    },
    {pong,     "pong"    },
    {play,     "play"    },
    {pause_,   "pause"   },
    {s_time,   "s_time"  },
    {s_nick,   "s_nick"  },
    {sync_,    "sync"    },
    {s_src,    "s_src"   },
    {s_access, "s_access"}
})


#endif //WATCH_UP_PROJECT_TYPES_HPP
