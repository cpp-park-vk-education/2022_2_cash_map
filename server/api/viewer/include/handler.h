#ifndef WATCH_UP_PROJECT_HANDLER_H
#define WATCH_UP_PROJECT_HANDLER_H

#include <string>
#include <memory>


#include "room.h"
#include "types.hpp"
#include "serializer.h"

typedef std::shared_ptr<IRoom> room_ptr;
typedef std::shared_ptr<IViewer> viewer_ptr;

class handler {
public:
    handler(std::string&& msg, const viewer_ptr& viewer, const room_ptr& room);
    void define_type(){
        auto it = types.find(req_["type"]);
        type_ = it->second;
    }
    void handle_request(){
        try{
            req_=serializer::deserialize(str_req_);
            define_type();
            switch (type_) {
                case leave:

                    // TODO send ok
                    break;
                case pong:
                    // TODO implement
                    break;
                case play:
                    if(!viewer->get_a_opts().can_pause){
                        // TODO send forbidden
                        return;
                    }
                    room_->play();
                    // TODO send ok
                    break;
                case pause_:
                    if(!viewer->get_a_opts().can_pause){
                        // TODO send forbidden
                        return;
                    }
                    room_->pause();
                    // TODO send ok
                    break;
                case s_time:
                    if(!viewer->get_a_opts().can_rewind){
                        // TODO send forbidden
                        return;
                    }
                    // TODO change signature
                    room_->synchronize();
                    // TODO send ok
                    break;
                case s_nick:
                    if(viewer->get_nickname() == req_["nick"]){
                        // TODO send ok
                        return;
                    }
                    room_->set_nickname(viewer->get_id(), std::move(req_["nick"]));
                    break;
                case sync_:
                    if(!viewer->get_a_opts().is_host){
                        // TODO send forbidden
                        return;
                    }
                    room_->synchronize();
                    break;
                case s_src:
                    if(!viewer->get_a_opts().is_host){
                        // TODO send forbidden
                        return;
                    }
                    room_->set_resource(req_["src"]);
                    //TODO send ok
                    break;
                case s_access: {
                    if (!viewer->get_a_opts().is_host) {
                        // TODO send forbidden
                        return;
                    }
                    auto opts = serializer::deserialize_access_opts(req_["opts"]);
                    access_options to_set {opts["pause"], opts["rewind"], opts["host"]};
                    room_->get_viewer(boost::lexical_cast<uuid>(req_["viewer"])).lock()->set_access_opts(to_set);

                    break;
                }
                default:

                    break;
            }
        }
        catch (...){

        }


    }
private:
    type type_ = invalid;
    viewer_ptr viewer;
    room_ptr room_;
    std::string str_req_;
    std::unordered_map<std::string, std::string> req_;
};

#endif //WATCH_UP_PROJECT_HANDLER_H
