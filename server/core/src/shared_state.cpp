#include "shared_state.h"

#include <iostream>

shared_state::shared_state(net::io_context &ioc):
        ioc_(ioc)
{}

void shared_state::add_room(const uuid &room_id, w_room_ptr&& room){
    rooms_.insert(std::make_pair(room_id, std::forward<w_room_ptr>(room)));
}

void shared_state::remove_room(uuid room_id) {
    rooms_.erase(room_id);
    std::cout << "[rooms count] : " << rooms_.size() << std::endl;
}

net::io_context &shared_state::get_io_context() const {
    return ioc_;
}

w_room_ptr shared_state::get_room(uuid room_id) {
    auto it = rooms_.find(room_id);
    if(it == rooms_.end()){
        return {};
    }
    return it->second;
}
