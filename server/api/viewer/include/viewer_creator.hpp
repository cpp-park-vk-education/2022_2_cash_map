#ifndef WATCH_UP_PROJECT_VIEWER_CREATOR_HPP
#define WATCH_UP_PROJECT_VIEWER_CREATOR_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "viewer.h"
#include "user.h"

typedef boost::uuids::uuid uuid;

class viewer_creator {
public:
    static std::shared_ptr<Viewer> create_anonymous(stream_ptr&& ws, room_ptr&& room = nullptr){
        return std::make_shared<Viewer>
                (std::move(ws), boost::lexical_cast<std::string>(boost::uuids::random_generator()()), "anonymous", std::move(room));
    }

    static std::shared_ptr<Viewer> create(stream_ptr && ws, user_ptr&& user, room_ptr&& room = nullptr){
        return std::make_shared<Viewer>
                (std::move(ws), std::move(user), std::move(room));
    }

    static std::shared_ptr<Viewer> create_host(stream_ptr && ws,  user_ptr&& user){
        if (!user){
            return create_anonymous(std::move(ws));
        }
        access_options opts{true, true, true};
        return std::make_shared<Viewer>(std::move(ws), opts, std::move(user));
    }
};


#endif //WATCH_UP_PROJECT_VIEWER_CREATOR_HPP
