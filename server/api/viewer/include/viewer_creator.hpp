#ifndef WATCH_UP_PROJECT_VIEWER_CREATOR_HPP
#define WATCH_UP_PROJECT_VIEWER_CREATOR_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "viewer.h"

typedef boost::uuids::uuid uuid;

class viewer_creator {
public:
    static std::shared_ptr<Viewer> create_viewer(stream_ptr && ws, std::string nickname, room_ptr&& room = nullptr){
        return std::make_shared<Viewer>
                (std::move(ws), boost::uuids::random_generator()(), std::move(nickname), std::move(room));
    }

    static std::shared_ptr<Viewer> create_host(stream_ptr && ws, std::string nickname){
        access_options opts{true, true, true};
        return std::make_shared<Viewer>(std::move(ws), boost::uuids::random_generator()(), opts, std::move(nickname));
    }
};


#endif //WATCH_UP_PROJECT_VIEWER_CREATOR_HPP
