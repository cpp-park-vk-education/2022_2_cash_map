#include "include/domain/AppAutorizationManager.h"


AuthenticationStatus AppAuthorizationManager::authenticateUser(const QString &username, const QString &password) {
    // авторизация
    return Success;
};

bool AppAuthorizationManager::isThereAuthorizedUser() {
    return false;
};
