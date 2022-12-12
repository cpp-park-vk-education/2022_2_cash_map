#ifndef APPUSER_H
#define APPUSER_H

#include "include/domain/models/interface/User.h"


class AppUser : public User {
public:
    AppUser(std::string username);
    ~AppUser() = default;
    AppUser(AppUser &user) = default;
    AppUser(AppUser &&user) = default;
    AppUser &operator=(AppUser &user) = default;
    AppUser &operator=(AppUser &&user) = default;

    virtual std::string userName() override;
private:
    std::string username;
};


#endif // APPUSER_H
