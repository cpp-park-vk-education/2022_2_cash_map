#ifndef APPUSER_H
#define APPUSER_H

#include <QString>


class User  {
private:
    static User *instance;
    User() = default;
    User(User &user) = delete;
    User(User &&user) = delete;
    User &operator=(User &user) = delete;
    User &operator=(User &&user) = delete;
public:
    ~User() = default;

    static User *getInstance() {
        if (!instance) {
            instance = new User();
        }
        return instance;
    };

    static void setUserInfo(const QString &username, const QString &login, const QString &password) {
        if (instance) {
            instance->username = username;
            instance->login = login;
            instance->password = password;
        } else {
            throw "User isn't initialized.";
        }
    };

    void clear();

    bool initialized();

    QString getUserName();

    QString getLogin();

    QString getPassword();
    void setInstance(User *newInstance);


private:
    QString username;
    QString login;
    QString password;
};


#endif // APPUSER_H
