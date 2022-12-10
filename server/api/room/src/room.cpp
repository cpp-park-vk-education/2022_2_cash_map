#include "room.h"

#include <iostream>
#include <utility>

#include <boost/uuid/uuid_io.hpp>

#include "viewer.h"
#include "shared_state.h"
#include "serializer.h"
#include "response_creator.hpp"

Room::Room(uuid&& host, uuid&& id, state_ptr state):
        playing(false),
        id_(std::forward<uuid>(id)),
        host_(std::forward<uuid>(host)),
        state_(std::move(state)),
        check_timer_(state_->get_io_context(), boost::posix_time::seconds(5))
{
    std::cout << "[room constructor]\n";
}

void Room::start() {
    std::cout << "[room start]\n";
}

void Room::join(w_viewer_ptr viewer) {
    if(!viewers_.empty()) {
        auto welcome_msg = serializer::serialize_viewers(type::join, viewers_);
        viewer.lock()->send_message(welcome_msg);

        auto incomer_msg = serializer::serialize_viewers(type::join, {std::make_pair(viewer.lock()->get_id(), viewer.lock()->get_nickname())});
        for (const auto &p: participants_) {
            p.second.lock()->send_message(incomer_msg);
        }
    } else {
        auto res = response_creator::create_with_room(200, "created", id_);
        viewer.lock()->send_message(serializer::serialize_response(create, res));
    }
    participants_.insert(std::make_pair(viewer.lock()->get_id(), viewer));
    viewers_.emplace_back(viewer.lock()->get_id(), viewer.lock()->get_nickname());
}

void Room::leave(const uuid& id, const std::string& nick) {
    auto viewer_dto = std::make_pair(id, nick);
    auto it = find(viewers_.begin(), viewers_.end(), viewer_dto);
    participants_.erase(id);
    viewers_.erase(it);
    auto leave_msg = serializer::serialize_viewers(type::leave, {viewer_dto});
    for(const auto& p : participants_){
        p.second.lock()->send_message(leave_msg);
    }
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
    for(const auto& viewer : participants_){
        viewer.second.lock()->send_message("ping");
    }
    start_timer();
}

void Room::pause() {
    if(!playing){
        return;
    }
    playing = false;
    for(const auto& p : participants_){
        p.second.lock()->send_message("");;
    }
}

void Room::play() {
    if(playing){
        return;
    }
    playing = true;
    for(const auto& p : participants_){
        p.second.lock()->send_message("");
    }
    start_timer();
}

void Room::synchronize(const boost::posix_time::time_duration & timing) {
    auto msg = serializer::serialize_response(s_time,
                                              response_creator::create_with_timing(timing));
    for(const auto& p : participants_){
        p.second.lock()->send_message("");
    }
}

void Room::send_chat_msg(uuid /*viewer*/, const std::string &/*msg*/) {
    for(const auto& p : participants_){
        p.second.lock()->send_message("");
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

void Room::set_resource(const std::string & src) {
    src_ = src;
}

w_viewer_ptr Room::get_viewer(const uuid& v_id) {
    return participants_[v_id];
}

void Room::set_nickname(const uuid &viewer, std::string &&nick) {
    auto msg = serializer::serialize_viewers(s_nick, {std::make_pair(viewer, std::move(nick))});
    for(const auto& v: participants_){
        v.second.lock()->send_message(msg);
    }
}


