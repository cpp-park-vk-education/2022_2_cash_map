#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>
#include <string>


enum AuthorizationStatus {
    Success = 1,
    IncorrectEmailOrPassword = 2
};


class AuthorizationManager : public QObject {
    Q_OBJECT
public:
    virtual AuthorizationStatus authorizeUser(std::string username, std::string password) = 0;

    virtual bool isUserAuthorized() = 0;
};

#endif // AUTHORIZATIONMANAGER_H
