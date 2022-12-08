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

}

void Room::join(w_viewer_ptr viewer) {
    participants_.insert(std::make_pair(viewer.lock()->get_id(), viewer));
}

void Room::leave(uuid id) {
    participants_.erase(id);
}

void Room::check_timings() {
    std::cout << "[check timings] id: "<< boost::uuids::to_string(id_)<< std::endl;
    if(participants_.empty()){
        return;
    }
    if(!playing){
        stop_timer();
        return;
    }
    std::cout << "[check timings]\n";
    start_timer();
}

void Room::pause() {
    if(!playing){
        return;
    }
    playing = false;
    for(const auto& p : participants_){
        p.second.lock()->pause();
    }
}

void Room::play() {
    if(playing){
        return;
    }
    playing = true;
    for(const auto& p : participants_){
        p.second.lock()->play();
    }
    start_timer();
}

void Room::synchronize() {
    for(const auto& p : participants_){
        p.second.lock()->set_timestamp();
    }
}

void Room::send_chat_msg(uuid /*viewer*/, const std::string &/*msg*/) {
    for(const auto& p : participants_){
        p.second.lock()->send_chat_msg("");
    }
}


const uuid Room::get_id() const {
    return id_;
}

Room::~Room() {
    state_->remove_room(id_);
    std::cout << "[room destructor]\n";
}

void Room::start_timer() {
    check_timer_.expires_from_now(boost::posix_time::seconds(5));
    check_timer_.async_wait([self{shared_from_this()}](const error_code& ec){
        if(ec){
            std::cout << "[check timings error] " << ec.message() << std::endl;
        }
        self->check_timings();
    });
}

void Room::stop_timer() {
    check_timer_.cancel();
}

void Room::set_resource(const std::string &) {

}

w_viewer_ptr Room::get_viewer(const uuid& v_id) {
    return participants_[v_id];
}


