#ifndef SERVER_USER_CREATOR_H
#define SERVER_USER_CREATOR_H

#include "user_session.h"

class user_creator{
public:
    static std::shared_ptr<user_session> create(stream_ptr&& ws, user_ptr&& user, const state_ptr& state){
        return std::make_shared<user_session>(std::move(ws), std::move(user), state);
    }
};
#endif //SERVER_USER_CREATOR_H
