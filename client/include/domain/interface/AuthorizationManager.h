#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>


enum AuthenticationStatus {
    Success = 1,
    IncorrectLoginOrPassword = 2
};


class AuthorizationManager : public QObject {
    Q_OBJECT
public:
    virtual AuthenticationStatus authenticateUser(const QString &login, const QString &password) = 0;

    virtual bool isThereAuthorizedUser() = 0;
};

#endif // AUTHORIZATIONMANAGER_H
