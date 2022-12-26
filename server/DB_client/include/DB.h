#ifndef SERVER_DB_H
#define SERVER_DB_H

#include <unordered_map>
#include <memory>

#include "user.h"


class DB {
public:
    static DB& get_instance();
    std::unique_ptr<User> get_user_by_id(const std::string& id, const std::string& pass);
    bool add_user(const std::string& nickname, const std::string& login, const std::string& password);

    DB(const DB& ) = delete;
    void operator=(const DB&) = delete;
private:
    DB()= default;


    std::unordered_map<std::string, std::pair<User, std::string>> users;
};

#endif //SERVER_DB_H
