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

    static nlohmann::json parse(const std::string& json_str){
        return nlohmann::json::parse(json_str);
    }

    static std::unordered_map<std::string, std::string> deserialize(const std::string& json_str){
        //TODO try-catch
        nlohmann::json json =  nlohmann::json::parse(json_str);
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
            data[item.key()] = boost::lexical_cast<uuid>(item.value());
        }
        return data;
    }
};

#endif //WATCH_UP_PROJECT_SERIALIZER_H
