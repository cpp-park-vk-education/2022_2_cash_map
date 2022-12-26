#include "room.h"

#include <iostream>
#include <utility>

#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>

#include "viewer.h"
#include "shared_state.h"
#include "serializer.h"
#include "response_creator.hpp"

Room::Room(std::string&& host, uuid&& id, state_ptr state):
        playing(false),
        id_(std::forward<uuid>(id)),
        host_(std::move(host)),
        state_(std::move(state)),
        check_timer_(state_->get_io_context(), boost::posix_time::seconds(5))
{

    std::cout << "[room constructor]\n";
}

void Room::start() {
    std::cout << "[room start]\n";
    start_timer();
}

void Room::join(w_viewer_ptr viewer) {
    std::cout << "[ROOM JOIN]\n";
    if(participants_.find(viewer.lock()->get_id()) != participants_.end()){
        participants_[viewer.lock()->get_id()].lock()->set_room(nullptr);
        participants_[viewer.lock()->get_id()] = viewer;
        auto welcome_msg = serializer::serialize_welcome_msg("join", viewers_, src_, calculate_timestamp(),
                                                             playing, id_,  service_, viewer.lock()->get_id());
        viewer.lock()->send_message(welcome_msg);
        return;
    }
    if(!viewers_.empty()) {

        auto welcome_msg = serializer::serialize_welcome_msg("join", viewers_, src_, calculate_timestamp(), playing, id_, service_);
        viewer.lock()->send_message(welcome_msg);

        auto incomer_msg = serializer::serialize_viewers("incomer", {std::make_pair(viewer.lock()->get_id(), viewer.lock()->get_nickname())});
        for (const auto &p: participants_) {
            std::cout << incomer_msg << std::endl;
            p.second.lock()->send_message(incomer_msg);
        }
    } else {
        auto res = response_creator::create_with_room(200, "created", id_);
        viewer.lock()->send_message(serializer::serialize_response("create", res));
    }

    participants_.insert(std::make_pair(viewer.lock()->get_id(), viewer));
    viewers_.emplace_back(viewer.lock()->get_id(), viewer.lock()->get_nickname());
    latency_.insert(std::make_pair(viewer.lock()->get_id(), boost::posix_time::time_duration(0,0,0,0)));
}

void Room::leave(const std::string& id, const std::string& nick){
    std::cout << "[ROOM LEAVE]\n";
    auto viewer_dto = std::make_pair(id, nick);
    auto it = find(viewers_.begin(), viewers_.end(), viewer_dto);
    viewers_.erase(it);
    participants_.erase(id);
    latency_.erase(id);
    auto leave_msg = serializer::serialize_viewers("leave", {viewer_dto});
    for(const auto& p : participants_){
        p.second.lock()->send_message(leave_msg);
    }
    if (participants_.empty()){
        stop_timer();
    }
}



void Room::pause(const boost::posix_time::time_duration & time, const std::string& sender_id) {
    if(!playing){
        return;
    }
    playing = false;
    auto msg = serializer::serialize_response("pause", {{"time", boost::lexical_cast<std::string>(time)}});
    for(const auto& p : participants_){
        if(p.first != sender_id)
            p.second.lock()->send_message(msg);
    }
}

void Room::play(const std::string& sender_id) {
    if(playing){
        return;
    }
    playing = true;
    auto msg = serializer::serialize_response("play", {});
    for(const auto& p : participants_){
        if (p.first != sender_id){
            p.second.lock()->send_message(msg);

            std::cout << p.second.lock()->get_nickname() << " " << msg << std::endl;
        }
    }

}

void Room::synchronize(const boost::posix_time::time_duration & timing) {
    auto msg = serializer::serialize_response("s_time",
                                              response_creator::create_with_timing(timing));

    for(const auto& p : participants_){
        p.second.lock()->send_message(msg);
    }
}

void Room::send_chat_msg(const std::string& nick, const std::string &msg) {
    auto res = response_creator::create_chat_mag(nick, msg);
    for(const auto& p : participants_){
        p.second.lock()->send_message(res);
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
        self->ping();
    });
}

void Room::stop_timer() {
    check_timer_.cancel();
}

void Room::set_resource(const std::string &src, const std::string &viewer_id) {
    src_ = src;
    playing = false;
    current_timestamp = boost::posix_time::time_duration(0,0,0,0);

    std::unordered_map<std::string, std::string> res{
            {"src", src}
    };
    auto msg = serializer::serialize_response("s_src", res);
    for(const auto& p : participants_){
        if(p.first != viewer_id){
            p.second.lock()->send_message(msg);
        }
    }
}

w_viewer_ptr Room::get_viewer(const std::string& v_id) {
    return participants_[v_id];
}

void Room::set_nickname(const std::string &viewer, std::string &&nick) {
    auto msg = serializer::serialize_viewers("s_nick", {std::make_pair(viewer, std::move(nick))});
    for(const auto& v: participants_){
        v.second.lock()->send_message(msg);
    }
}


void Room::ping(){
    std::cout << "[check timings] id: "<< boost::uuids::to_string(id_)<< std::endl;
    if(participants_.empty()){
        return;
    }
    auto ping_time = boost::posix_time::microsec_clock::universal_time();
    auto msg = response_creator::create_ping(ping_time);

    for(const auto& viewer : participants_){
        viewer.second.lock()->send_message(msg);
    }
    last_server_time = ping_time;
    start_timer();
}


void Room::on_pong(std::unordered_map<std::string, std::string> &req) {
    ping_info ping{
        boost::posix_time::duration_from_string(req["time"]),
        // TODO server time from response
        boost::posix_time::microsec_clock::universal_time() - last_server_time
        /*boost::posix_time::time_from_string(req["server_time"])*/,
        boost::posix_time::microsec_clock::universal_time(),
        req["v_id"]
    };
    if(ping.player_time > current_timestamp){
        if(playing){
            current_timestamp = ping.player_time + ping.latency;
        } else {
            current_timestamp = ping.player_time;
        }
        last_update = boost::posix_time::microsec_clock::universal_time();
    }

    latency_[ping.viewer_id] = ping.latency;
    for(const auto& v : participants_){
        boost::posix_time::time_duration pong_time = playing ? ping.player_time + latency_[v.first] : ping.player_time;
        auto msg = response_creator::create_pong(pong_time, ping.viewer_id);
        v.second.lock()->send_message(msg);
    }
}

state_ptr Room::get_state() {
    return state_;
}


bool Room::is_playing(){
    return playing;
}

std::string Room::calculate_timestamp() {
    std::stringstream ss_time;
    auto timestamp = current_timestamp + (boost::posix_time::microsec_clock::universal_time() - last_update);
    ss_time << timestamp;
    return ss_time.str();
}

void Room::set_service(const std::string &service, const std::string &viewer) {
    playing = false;
    service_ = service;
    src_ = "";
    current_timestamp = boost::posix_time::time_duration(0,0,0,0);
    std::unordered_map<std::string, std::string> res{
            {"service", service}
    };
    auto msg = serializer::serialize_response("s_service", res);
    for(const auto& p : participants_){
        if(p.first != viewer){
            p.second.lock()->send_message(msg);
        }
    }
}

void Room::service(const std::string & service) {
    service_ = service;
}
