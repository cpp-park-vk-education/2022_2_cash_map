#include "serializer.h"

std::unordered_map<std::string, std::string> serializer::deserialize(const std::string &json_str) {
        //TODO try-catch
        nlohmann::json json = nlohmann::json::parse(json_str);
        std::unordered_map<std::string, std::string> data{};

        for(const auto& item: json.items()){

            data[item.key()] = item.value();
        }
        return data;
}

std::unordered_map<std::string, bool> serializer::deserialize_access_opts(const std::string &json_str) {
        nlohmann::json json =  nlohmann::json::parse(json_str);
        std::unordered_map<std::string, bool> data{};

        for(const auto& item: json.items()){
            data[item.key()] = boost::lexical_cast<bool>(item.value());
        }
        return data;
}

std::string serializer::serialize_viewers(std::string type, const std::vector<std::pair<std::string, std::string>> &viewers) {
    nlohmann::json data{};
    data["type"] = type;
    auto viewers_arr = nlohmann::json::array();
    for(const auto& viewer: viewers){
        auto v_obj = nlohmann::json{};
        v_obj["id"] = viewer.first;
        v_obj["nick"] = viewer.second;
        viewers_arr.push_back(v_obj);
    }
    data["viewers"] = viewers_arr;
    return nlohmann::to_string(data);
}

std::string serializer::serialize_welcome_msg(std::string type, const std::vector<std::pair<std::string, std::string>> &viewers,
                                  std::string src, std::string timing, bool state, const uuid &room_id, const std::string& service,
                                  const std::string &self) {
        nlohmann::json data{};
        data["type"] = type;
        data["src"] = src;
        data["time"] = timing;
        data["code"] = "200";
        data["state"] = state ? "True" : "False";
        data["room_id"] = boost::lexical_cast<std::string>(room_id);
        data["service"] = service;
        auto viewers_arr = nlohmann::json::array();
        for(const auto& viewer: viewers){
            if (viewer.first == self){
                continue;
            }
            auto v_obj = nlohmann::json{};
            v_obj["id"] = viewer.first;
            v_obj["nick"] = viewer.second;
            viewers_arr.push_back(v_obj);
        }
        data["viewers"] = viewers_arr;
        return nlohmann::to_string(data);
}

std::string serializer::serialize_response(std::string type, const std::unordered_map<std::string, std::string>& fields){
        nlohmann::json data{};
        data["type"] = type;
        for(const auto& [key, value] : fields){
            data[key] = value;
        }
        return nlohmann::to_string(data);
}
std::string serializer::serialize_timings(std::string type, const std::vector<std::pair<std::string, std::string>>& timings){
        nlohmann::json data{};
        data["type"] = type;
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
