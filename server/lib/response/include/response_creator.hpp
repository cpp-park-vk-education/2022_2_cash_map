#ifndef WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP
#define WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP

#include <unordered_map>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "serializer.h"

class response_creator {
public:
    static std::string create_with_status(std::string type_, unsigned short code);

    static std::unordered_map<std::string, std::string>
    create_with_room(unsigned short code, const std::string &msg, const uuid &room_id);

    static std::unordered_map<std::string, std::string> create_with_timing
            (const boost::posix_time::time_duration &time);

    static std::string create_ping(const boost::posix_time::ptime &server_time);

    static std::string
    create_login(std::string type_, unsigned short code, const std::string &login, const std::string &nick,
                 const std::string &pass);

    static std::string create_src_success(std::string type_, unsigned short code, const std::string &src);

    static std::string create_chat_mag(const std::string &nick, const std::string &msg);

    static std::string create_pong(const boost::posix_time::time_duration& timestamp, const std::string& viewer_id);
};
#endif //WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP
