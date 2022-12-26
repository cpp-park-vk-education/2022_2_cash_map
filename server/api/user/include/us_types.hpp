#ifndef SERVER_US_TYPES_HPP
#define SERVER_US_TYPES_HPP


enum class us_type{
    invalid,
    create,
    join,
    logout,
};

static std::unordered_map<std::string, us_type> const us_types = {
        {"invalid", us_type::invalid},
        {"create", us_type::create},
        {"join", us_type::join},
        {"logout", us_type::logout}
};


static std::unordered_map<us_type, std::string> const us_types_to_string ={
        {us_type::invalid, "invalid"},
        {us_type::create,"create"},
        {us_type::join,"join"},
        {us_type::logout,"logout"}
};
#endif //SERVER_US_TYPES_HPP
