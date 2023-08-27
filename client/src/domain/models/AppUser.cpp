#include "include/domain/models/AppUser.h"
#include "qdebug.h"

User *User::instance = nullptr;


void User::clear() {
    username = nullptr;
    login = nullptr;
    password = nullptr;
}

bool User::initialized() {
    if (login == nullptr || password == nullptr || username == nullptr) {
        return false;
    }
    return true;
}

QString User::getUserName() {
    if (username != nullptr) {
        return *username;
    }
    return QString();
}


QString User::getPassword() {
    if (username != nullptr) {
        return *password;
    }
    return QString();
}

QString User::getLogin() {
    if (username != nullptr) {
        return *login;
    }
    return QString();
}

User::~User() {
    delete password;
    delete login;
    delete username;
}
