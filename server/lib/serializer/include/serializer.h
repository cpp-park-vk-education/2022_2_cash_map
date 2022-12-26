#ifndef WATCH_UP_PROJECT_SERIALIZER_H
#define WATCH_UP_PROJECT_SERIALIZER_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>

using uuid = boost::uuids::uuid;

class serializer {
public:

    static std::unordered_map<std::string, std::string> deserialize(const std::string& json_str);

    static std::unordered_map<std::string, bool> deserialize_access_opts(const std::string& json_str);


    static std::string serialize_viewers(std::string type, const std::vector<std::pair<std::string, std::string>>& viewers);

    static std::string serialize_welcome_msg(std::string type, const std::vector<std::pair<std::string, std::string>>& viewers,
                                             std::string src, std::string timing, bool state, const uuid& room_id,  const std::string& service,
                                             const std::string& self = "");

    static std::string serialize_response(std::string type, const std::unordered_map<std::string, std::string>& fields);

    static std::string serialize_timings(std::string type, const std::vector<std::pair<std::string, std::string>>& timings);


    };
#endif //WATCH_UP_PROJECT_SERIALIZER_H
