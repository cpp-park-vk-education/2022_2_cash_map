#ifndef WATCH_UP_PROJECT_SERIALIZER_H
#define WATCH_UP_PROJECT_SERIALIZER_H

#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>

#include "types.hpp"

using uuid = boost::uuids::uuid;

class serializer {
public:

    static std::unordered_map<std::string, std::string> deserialize(const std::string& json_str){
        //TODO try-catch
        nlohmann::json json = nlohmann::json::parse(json_str);
        std::unordered_map<std::string, std::string> data{};

        for(const auto& item: json.items()){

            data[item.key()] = item.value();
        }
        return data;
    }

    static std::unordered_map<std::string, bool> deserialize_access_opts(const std::string& json_str){
        nlohmann::json json =  nlohmann::json::parse(json_str);
        std::unordered_map<std::string, bool> data{};

        for(const auto& item: json.items()){
            data[item.key()] = boost::lexical_cast<bool>(item.value());
        }
        return data;
    }


    static std::string serialize_viewers(type type_, const std::vector<std::pair<uuid, std::string>>& viewers){
        nlohmann::json data{};
        data["type"] = type_;
        auto viewers_arr = nlohmann::json::array();
        for(const auto& viewer: viewers){
            auto v_obj = nlohmann::json{};
            v_obj["id"] = boost::lexical_cast<std::string>(viewer.first);
            v_obj["nick"] = viewer.second;
            viewers_arr.push_back(v_obj);
        }
        data["viewers"] = viewers_arr;
        return nlohmann::to_string(data);
    }


    static std::string serialize_response(type type_, const std::unordered_map<std::string, std::string>& fields){
        nlohmann::json data{};
        data["type"] = type_;
        for(const auto& [key, value] : fields){
            data[key] = value;
        }
        return nlohmann::to_string(data);
    }

    static std::string serialize_timings(type type_, const std::vector<std::pair<std::string, std::string>>& timings){
        nlohmann::json data{};
        data["type"] = type_;
        auto viewers_arr = nlohmann::json::array();
        for(const auto& viewer: timings){
            auto v_obj = nlohmann::json{};
            v_obj["id"] = viewer.first;
            v_obj["time"] = viewer.second;
            viewers_arr.push_back(v_obj);
        }
        data["timings"] = viewers_arr;
        return nlohmann::to_string(data);
    }



};
#endif //WATCH_UP_PROJECT_SERIALIZER_H
