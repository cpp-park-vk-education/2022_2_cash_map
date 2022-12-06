#ifndef WATCH_UP_PROJECT_SERIALIZER_H
#define WATCH_UP_PROJECT_SERIALIZER_H

#include <string>

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

    static type get_type(const std::string& json_str){
        auto json = parse(json_str);
        return json["type"].get<type>();
    }

    static uuid get_room_id(const std::string& json_str){
        auto json = parse(json_str);
        return boost::lexical_cast<uuid>
                (std::string(json["room_id"]));
    }
};

#endif //WATCH_UP_PROJECT_SERIALIZER_H
