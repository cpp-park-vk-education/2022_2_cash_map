#include "include/domain/models/AppUser.h"



AppUser::AppUser(std::string username) : username(username) {};

std::string AppUser::userName() {
    return username;
}
