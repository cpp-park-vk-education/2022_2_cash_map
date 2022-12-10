#ifndef WATCH_UP_PROJECT_ROOM_CREATOR_HPP
#define WATCH_UP_PROJECT_ROOM_CREATOR_HPP

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "room.h"
#include "shared_state.h"

typedef boost::uuids::uuid uuid;


class room_creator{
public:
    static std::shared_ptr<Room> create_room(const std::weak_ptr<Viewer>& host, state_ptr state){
        return std::make_shared<Room>(host.lock()->get_id(), boost::uuids::random_generator()(), std::move(state));
    }
};

#endif //WATCH_UP_PROJECT_ROOM_CREATOR_HPP
