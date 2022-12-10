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
