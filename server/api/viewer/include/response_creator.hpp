#ifndef WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP
#define WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP

#include <unordered_map>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "serializer.h"
#include "types.hpp"

class response_creator{
public:
    static std::unordered_map<std::string, std::string> create_with_status(unsigned short code, const std::string& msg){
        std::unordered_map<std::string, std::string> data{};
        data["code"] = std::to_string(code);
        data["message"] = msg;
        return data;
    }
    static std::unordered_map<std::string, std::string> create_with_room(unsigned short code, const std::string& msg, const uuid& room_id){
        std::unordered_map<std::string, std::string> data{};
        data["code"] = std::to_string(code);
        data["message"] = msg;
        data["room_id"] = boost::lexical_cast<std::string>(room_id);
        return data;
    }

    static std::unordered_map<std::string, std::string> create_with_timing
    (const boost::posix_time::time_duration& time){
        std::unordered_map<std::string, std::string> data{};
        std::stringstream ss_time;
        ss_time << time;
        auto str_time = ss_time.str();
        data["time"] = str_time;
        return data;
    }

    static std::unordered_map<std::string, std::string> create_ping(const boost::posix_time::ptime& server_time){
        ;
        std::unordered_map<std::string, std::string> data{};
        std::stringstream ss_time;
        ss_time << server_time;
        data["time"] = ss_time.str();
        return data;
    }
};
#endif //WATCH_UP_PROJECT_RESPONSE_CREATOR_HPP
