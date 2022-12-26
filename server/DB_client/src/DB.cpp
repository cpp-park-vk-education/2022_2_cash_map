#include "DB.h"


DB &DB::get_instance() {
    static DB instance;
    return instance;
}

std::unique_ptr<User> DB::get_user_by_id(const std::string& id, const std::string& pass) {
    auto it = users.find(id);
    if(it == users.end()){
        return {};
    }
    if(it->second.second != pass){
        return {};
    }
    return std::make_unique<User>(it->second.first);
}

bool DB::add_user(const std::string& nickname, const std::string& login, const std::string& password) {
    if(login.empty())
        return false;
    if(users.find(login) == users.end()){
        User new_user;
        new_user.set_nick(nickname);
        new_user.set_id(login);
        new_user.set_pass(password);
        users.insert({login, {new_user,password}});
        return true;
    }
    return false;
}
