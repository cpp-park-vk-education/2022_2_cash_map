#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>

#include <include/network/NetworkManager.h>


enum AuthenticationStatus {
    Authorized = 1,
    IncorrectLoginOrPassword = 2,
    LogoutSucceeded = 3,
    LogoutFailed = 4

};

enum RegistrationStatus {
    Registered = 1,
    LoginInUse = 2
};


class AuthorizationManager : public QObject {
    Q_OBJECT
public:
    virtual void authenticateUser(const QString &login, const QString &password) = 0;

    virtual void registerUser(const QString &username, const QString &login, const QString &password) = 0;

    virtual bool isThereAuthorizedUser() = 0;
public slots:
    virtual void processResponse(const QVariantMap &response) = 0;
    virtual void logout() = 0;
signals:
    void authResponseSignal(AuthenticationStatus);
    void registrationSignal(RegistrationStatus);
    void logoutSignal(AuthenticationStatus);
};

#endif // AUTHORIZATIONMANAGER_H
