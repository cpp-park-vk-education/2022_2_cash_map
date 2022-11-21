#ifndef WATCH_UP_PROJECT_SHARED_STATE_H
#define WATCH_UP_PROJECT_SHARED_STATE_H

#include <memory>
#include <vector>

#include "room.h"


typedef std::shared_ptr<IRoom> room_ptr;

class Shared_state{
public:
    std::vector<room_ptr> rooms_;
};

#endif //WATCH_UP_PROJECT_SHARED_STATE_H
