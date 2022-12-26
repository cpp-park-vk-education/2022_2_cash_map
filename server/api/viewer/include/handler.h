#ifndef WATCH_UP_PROJECT_HANDLER_H
#define WATCH_UP_PROJECT_HANDLER_H

#include <string>
#include <memory>
#include <utility>

#include "room.h"
#include "vs_types.hpp"
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
        if (it == types.end())
            return;
        type_ = it->second;
    }
    void handle_request(){
        try{
            req_=serializer::deserialize(str_req_);
            std::cout <<"[viewer handle request]\n" << str_req_ << std::endl;
            define_type();
            switch (type_) {
                case vs_type::leave:
                    viewer_->do_close();
                    return;
                case vs_type::pong:
                    req_["v_id"] = boost::lexical_cast<std::string>(viewer_->get_id());
                    room_->on_pong(req_);
                    viewer_->do_read();
                    return;
                case vs_type::play: {
                    if (!viewer_->get_a_opts().can_pause) {
                        status_ = 403;
                        break;
                    }
                    if (room_->is_playing()){
                        status_ = 409;
                        break;
                    }
                    status_ = 200;
                    room_->play(viewer_->get_id());
                }
                    break;
                case vs_type::pause_: {
                    if (!viewer_->get_a_opts().can_pause) {
                        status_ = 403;
                        break;
                    }
                    if (!room_->is_playing()){
                        status_ = 409;
                        break;
                    }
                    room_->pause(boost::lexical_cast<boost::posix_time::time_duration>(req_["time"]), viewer_->get_id());
                    status_ = 200;
                }
                    break;
                case vs_type::s_time: {
                    if (!viewer_->get_a_opts().can_rewind) {
                        status_ = 403;
                        break;
                    }
                    status_ = 200;
                    room_->synchronize(boost::lexical_cast<boost::posix_time::time_duration>(req_["time"]));
                }
                    break;
                case vs_type::s_nick:
                    if (viewer_->get_nickname() == req_["nick"]) {
                        status_ = 200;
                        break;
                    }
                    viewer_->set_nickname(req_["nick"]);
                    room_->set_nickname(viewer_->get_id(), std::move(req_["nick"]));
                    status_ = 200;
                    break;
                case vs_type::sync_: {
                    if (!viewer_->get_a_opts().is_host) {
                        status_ = 403;
                        break;
                    }
                    status_ = 200;
                    room_->synchronize(boost::posix_time::duration_from_string(req_["time"]));
                }
                    break;
                case vs_type::s_src: {
                    if (!viewer_->get_a_opts().is_host) {
                        status_ = 403;
                        break;
                    }
                    status_ = 200;
                    room_->set_resource(req_["src"], viewer_->get_id());

                }
                    break;
                case vs_type::s_access: {
                    if (!viewer_->get_a_opts().is_host) {
                        status_ = 403;
                        break;
                    }
                    access_options to_set {boost::lexical_cast<bool>(req_["pause"]),
                                           boost::lexical_cast<bool>(req_["rewind"]),
                                           boost::lexical_cast<bool>(req_["host"])};
                    room_->get_viewer(req_["viewer"]).lock()->set_access_opts(to_set);
                    status_ = 200;
                    break;
                }
                case vs_type::chat: {
                    room_->send_chat_msg(viewer_->get_nickname(), req_["msg"]);
                    break;
                }
                case vs_type::s_service: {
                    if(!viewer_->get_a_opts().is_host){
                        status_ = 403;
                        break;
                    }
                    status_=200;
                    room_->set_service(req_["service"], viewer_->get_id());
                    break;
                }
                default:
                    status_ = 405;
                    break;
            }
        }
        catch (nlohmann::json::exception& ec){
            status_ = 400;
            std::cout << ec.what() << std::endl;
        }
        catch(boost::bad_lexical_cast const& e){
            std::cout << "Error: " << e.what() << "\n";
        }
        catch(...){
            std::cout << "ex\n";
            status_ = 400;
        }
        std::string msg;
        if(type_ == vs_type::s_src){
            msg = response_creator::create_src_success(type_to_string.at(type_), status_, req_["src"]);
            viewer_->send_message(msg);
        } else if(type_ != vs_type::chat){
            msg = response_creator::create_with_status(type_to_string.at(type_), status_);
            viewer_->send_message(msg);
        }
        viewer_->do_read();
    }
private:
    vs_type type_ = vs_type::invalid;
    unsigned short status_;
    viewer_ptr viewer_;
    room_ptr room_;
    std::string str_req_;
    std::unordered_map<std::string, std::string> req_;
};

#endif //WATCH_UP_PROJECT_HANDLER_H
