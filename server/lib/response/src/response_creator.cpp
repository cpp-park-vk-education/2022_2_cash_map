#include "response_creator.hpp"

std::string response_creator::create_with_status(std::string type_, unsigned short code){
    std::unordered_map<std::string, std::string> data{};
    data["code"] = std::to_string(code);
    auto out = serializer::serialize_response(type_, data);
    return out;
}
std::unordered_map<std::string, std::string> response_creator::create_with_room(unsigned short code, const std::string& msg, const uuid& room_id){
    std::unordered_map<std::string, std::string> data{};
    data["code"] = std::to_string(code);
    data["message"] = msg;
    data["room_id"] = boost::lexical_cast<std::string>(room_id);
    return data;
}

std::unordered_map<std::string, std::string> response_creator::create_with_timing
        (const boost::posix_time::time_duration& time){
    std::unordered_map<std::string, std::string> data{};
    std::stringstream ss_time;
    ss_time << time;
    auto str_time = ss_time.str();
    data["time"] = str_time;
    return data;
}

std::string response_creator::create_ping(const boost::posix_time::ptime& server_time){
    std::unordered_map<std::string, std::string> data{};
    std::stringstream ss_time;
    ss_time << server_time;
    data["server_time"] = ss_time.str();
    return serializer::serialize_response("ping", data);
}

std::string response_creator::create_login(std::string type_, unsigned short code, const std::string& login, const std::string& nick, const std::string& pass){
    std::unordered_map<std::string, std::string> data{};
    data["code"] = std::to_string(code);
    data["login"] = login;
    data["nick"] = nick;
    data["password"] = pass;
    auto out = serializer::serialize_response(type_, data);
    return out;
}

std::string response_creator::create_src_success(std::string type_, unsigned short code,const std::string& src){
    std::unordered_map<std::string, std::string> data{};
    data["code"] = std::to_string(code);
    data["src"] = src;
    auto out = serializer::serialize_response(type_, data);
    return out;
}

std::string response_creator::create_chat_mag(const std::string& nick, const std::string& msg){
    std::unordered_map<std::string, std::string> data{};
    data["sender"] = nick;
    data["msg"] = msg;
    auto out = serializer::serialize_response("chat", data);
    return out;
}

std::string response_creator::create_pong(const boost::posix_time::time_duration &timestamp, const std::string &viewer_id) {
    std::unordered_map<std::string, std::string> data{};
    std::stringstream ss_time;
    ss_time << timestamp;
    data["time"] = ss_time.str();
    data["viewer"] = viewer_id;
    return serializer::serialize_response("pong", data);
}
