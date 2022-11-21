#include <include/domain/AppAutorizationManager.h>


AppAuthorizationManager::AppAuthorizationManager() : user(nullptr) {}

AppAuthorizationManager::~AppAuthorizationManager() {
    delete user;
}

AuthorizationStatus AppAuthorizationManager::authorizeUser(std::string username, std::string password) {
    // авторизация
    return Success;
};

bool AppAuthorizationManager::isUserAuthorized() {
    return true;
};
