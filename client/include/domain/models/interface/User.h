#ifndef USER_H
#define USER_H

#include <string>


class User {
public:
    virtual std::string userName() = 0;
};

#endif // USER_H
