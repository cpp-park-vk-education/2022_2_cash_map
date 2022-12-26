#ifndef SERVER_PS_TYPES_HPP
#define SERVER_PS_TYPES_HPP

#include <string>
#include <unordered_map>

enum class ps_type{
    login,
    reg,
    join,

};

static std::unordered_map<std::string, ps_type> const ps_types = {
        {"login", ps_type::login},
        {"reg",   ps_type::reg  },
        {"join",  ps_type::join }
};

static std::unordered_map<ps_type, std::string> const ps_type_to_string = {
        {ps_type::login, "login"},
        {ps_type::reg,   "reg"  },
        {ps_type::join,  "join" },
};

#endif //SERVER_PS_TYPES_HPP
