#include "room.h"

#include <iostream>
#include <utility>

#include <boost/uuid/uuid_io.hpp>

#include "viewer.h"
#include "shared_state.h"

Room::Room(w_host_ptr host, uuid id, state_ptr state):
        id_(id),
        host_(std::move(host)),
        state_(std::move(state)),
        check_timer_(state_->get_io_context(), boost::posix_time::seconds(5))
{
    std::cout << "[room constructor]\n";
}

void Room::start() {
    std::cout << "[room start]\n";
    check_timer_.async_wait([self{shared_from_this()}](const error_code& ec){
        if(ec){
            std::cout << "[room start error] " << ec.message() << std::endl;
        }
        self->check_timings();
    });
}

void Room::join(w_viewer_ptr viewer) {
    participants_.insert(std::make_pair(viewer.lock()->get_id(), viewer));
}

void Room::leave(uuid id) {
    participants_.erase(id);
}

void Room::check_timings() {
    std::cout << "[check timings] id: "<< boost::uuids::to_string(id_)<< std::endl;
    check_timer_.expires_at(check_timer_.expires_at() + boost::posix_time::seconds(5));
    std::cout << "[participants count] : " << participants_.size() << std::endl;
    if(participants_.empty()){
        return;
    }
    check_timer_.async_wait([self{shared_from_this()}](const error_code& ec){
        if(ec){
            std::cout << "[check timings error] " << ec.message() << std::endl;
        }
        self->check_timings();
    });
}

void Room::pause() {

}

void Room::play() {

}

void Room::synchronize() {

}

const uuid Room::get_id() const {
    return id_;
}

Room::~Room() {
    state_->remove_room(id_);
    std::cout << "[room destructor]\n";
}

