#ifndef WATCH_UP_PROJECT_HANDLER_H
#define WATCH_UP_PROJECT_HANDLER_H

#include <string>
#include <memory>
#include <utility>

#include "room.h"
#include "types.hpp"
#include "serializer.h"
#include "response_creator.hpp"

typedef std::shared_ptr<IRoom> room_ptr;
typedef std::shared_ptr<IViewer> viewer_ptr;

class handler {
public:
    handler(std::string&& msg, viewer_ptr  viewer, room_ptr  room):
    viewer_(std::move(viewer)),
    room_(std::move(room)),
    str_req_(std::move(msg))
    {}
    void define_type(){
        auto it = types.find(req_["type"]);
        std::cout << req_["type"] << std::endl;
        type_ = it->second;
    }
    void handle_request(){
        try{
            req_=serializer::deserialize(str_req_);
            define_type();
            switch (type_) {
                case leave:
                    viewer_->do_close();
                    break;
                case pong:
                    req_["v_id"] = boost::lexical_cast<std::string>(viewer_->get_id());
                    room_->on_pong(req_);
                    break;
                case play: {
                    if (!viewer_->get_a_opts().can_pause) {
                        auto msg_ = response_creator::create_with_status(403, "operation forbidden");
                        auto str_msg_ = serializer::serialize_response(play, msg_);
                        viewer_->send_message(str_msg_);
                        return;
                    }
                    auto msg = response_creator::create_with_status(200, "ok");
                    auto str_msg = serializer::serialize_response(play, msg);
                    room_->play();
                }
                    break;
                case pause_:
                    if(!viewer_->get_a_opts().can_pause){
                        auto msg_ = response_creator::create_with_status(403, "operation forbidden");
                        auto str_msg_ = serializer::serialize_response(pause_, msg_);
                        viewer_->send_message(str_msg_);
                        return;
                    }
                    room_->pause();
                    // TODO send ok
                    break;
                case s_time:
                    if(!viewer_->get_a_opts().can_rewind){
                        auto msg_ = response_creator::create_with_status(403, "operation forbidden");
                        auto str_msg_ = serializer::serialize_response(s_time, msg_);
                        viewer_->send_message(str_msg_);
                        return;
                    }

                    room_->synchronize(boost::lexical_cast<boost::posix_time::time_duration>(req_["time"]));
                    // TODO send ok
                    break;
                case s_nick:
                    if(viewer_->get_nickname() == req_["nick"]){
                        auto msg = response_creator::create_with_status(200, "ok");
                        auto str_msg = serializer::serialize_response(s_nick, msg);
                        viewer_->send_message(str_msg);
                        return;
                    }
                    viewer_->set_nickname(req_["nick"]);
                    room_->set_nickname(viewer_->get_id(), std::move(req_["nick"]));
                    break;
                case sync_:
                    if(!viewer_->get_a_opts().is_host){
                        // TODO send forbidden
                        return;
                    }
                    room_->synchronize(boost::lexical_cast<boost::posix_time::time_duration>(req_["time"]));
                    break;
                case s_src:
                    if(!viewer_->get_a_opts().is_host){
                        auto msg_ = response_creator::create_with_status(403, "operation forbidden");
                        auto str_msg_ = serializer::serialize_response(s_src, msg_);
                        viewer_->send_message(str_msg_);
                        return;
                    }
                    room_->set_resource(req_["src"]);
                    //TODO send ok
                    break;
                case s_access: {
                    if (!viewer_->get_a_opts().is_host) {
                        auto msg_ = response_creator::create_with_status(403, "operation forbidden");
                        auto str_msg_ = serializer::serialize_response(s_access, msg_);
                        viewer_->send_message(str_msg_);
                        return;
                    }

                    access_options to_set {boost::lexical_cast<bool>(req_["pause"]),
                                           boost::lexical_cast<bool>(req_["rewind"]),
                                           boost::lexical_cast<bool>(req_["host"])};
                    room_->get_viewer(boost::lexical_cast<uuid>(req_["viewer"])).lock()->set_access_opts(to_set);
                    break;
                }
                default:

                    break;
            }
        }
        // TODO replace with custom exceptions
        catch (nlohmann::json::exception& ec){
            std::cout << ec.what() << std::endl;
        }


    }
private:
    type type_ = invalid;
    viewer_ptr viewer_;
    room_ptr room_;
    std::string str_req_;
    std::unordered_map<std::string, std::string> req_;
};

#endif //WATCH_UP_PROJECT_HANDLER_H
