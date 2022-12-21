#include "include/domain/models/AppUser.h"

User *User::instance = nullptr;


void User::clear() {
    username = "";
    login = "";
    password = "";
}

bool User::initialized() {
    if (login == "" && password == "" && username == "") {
        return false;
    }
    return true;
}

QString User::getUserName() {
    return username;
}


QString User::getPassword() {
    return password;
}

QString User::getLogin() {
    return login;
}
