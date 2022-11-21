#ifndef WATCH_UP_PROJECT_AUTH_HPP
#define WATCH_UP_PROJECT_AUTH_HPP

#include <string>

class websocket;

class User {
 private:
    uint64_t id;
    std::string username;
 public:
    uint64_t getId();
    std::string getUsername();
    User(std::string username);
};

class Session {
 public:
    User user;
    websocket* socket;
    uint64_t room_id;
};

#endif //WATCH_UP_PROJECT_AUTH_HPP
