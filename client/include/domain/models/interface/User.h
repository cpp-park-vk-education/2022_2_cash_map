#ifndef USER_H
#define USER_H

#include <QString>


class User {
public:

    virtual QString getUserName() = 0;

    virtual QString getLogin() = 0;

    virtual QString getPassword() = 0;
};

#endif // USER_H
