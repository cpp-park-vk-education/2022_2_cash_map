#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <string>

class User {
public:
    const std::string get_nick() const{
        return nickname_;
    }
    const std::string get_id() const{
        return uuid_;
    }

    const std::string get_pass() const{
        return password_;

    }
    void set_nick(const std::string& nick){
        nickname_ = nick;
    }
    void set_id(const std::string id){
        uuid_ = id;
    }

    void set_pass(const std::string& pass){
        password_ = pass;
    }
private:
    std::string nickname_;
    std::string uuid_;
    std::string password_;
};

#endif //SERVER_USER_H
