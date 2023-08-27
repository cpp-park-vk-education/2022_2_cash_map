#ifndef APPUSER_H
#define APPUSER_H

#include <QString>


class User  {
private:
    static User *instance;
    User() : username(nullptr), login(nullptr), password(nullptr) {};
    User(User &user) = delete;
    User(User &&user) = delete;
    User &operator=(User &user) = delete;
    User &operator=(User &&user) = delete;
public:
    ~User();

    static User *getInstance() {
        if (!instance) {
            instance = new User();
        }
        return instance;
    };

    static void setUserInfo(const QString &username, const QString &login, const QString &password) {
        if (instance) {
            instance->username = new QString(username);
            instance->login = new QString(login);
            instance->password = new QString(password);
        } else {
            throw "User isn't initialized.";
        }
    };

    void clear();

    bool initialized();

    QString getUserName();

    QString getLogin();

    QString getPassword();


private:
    QString *username;
    QString *login;
    QString *password;
};


#endif // APPUSER_H
