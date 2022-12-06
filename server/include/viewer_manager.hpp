#ifndef WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
#define WATCH_UP_PROJECT_VIEWER_MANAGER_HPP

#include <string>
#include <boost/beast.hpp>
#include <utility>

#include "types.hpp"
#include "serializer.h"
#include "viewer_creator.hpp"
#include "room_creator.hpp"

namespace beast = boost::beast;
namespace websocket = beast::websocket;

typedef websocket::stream<beast::tcp_stream> stream;
typedef std::unique_ptr<stream> stream_ptr;

class viewer_manager {
public:
    viewer_manager() = delete;
    viewer_manager(std::string&& ws_req, stream_ptr&& ws, state_ptr state):
        ws_(std::move(ws)),
        state_(std::move(state)),
        ws_req_(std::move(ws_req))
    {}

    void do_close(){
        //TODO log close reason
        ws_->close("");
    }

    void define_type(){
        type_ = serializer::get_type(ws_req_);
    }

    void handle_request(){
        define_type();
        // TODO wrap whole block in try-catch
        if(type_ == create){
            auto host = viewer_creator::create_host(std::move(ws_));

            auto room = room_creator::create_room(std::weak_ptr(host), state_);
            state_->add_room(room->get_id(), std::weak_ptr(room));
            room->start();
            host->set_room(room);
            host->start();

        } else if(type_ == join){
            auto room_id = serializer::get_room_id(ws_req_);
            auto room = state_->get_room(room_id);
            if(!room.lock()){
                // TODO send not found
                return;
            }
            viewer_creator::create_viewer(std::move(ws_), room.lock())->start();
        } else if(type_ == invalid){
            // TODO send bad request
            return;
        } else {
           // TODO send method not allowed
        }
    }
private:
    stream_ptr ws_;
    state_ptr state_;

    type type_ = invalid;
    std::string ws_req_;

};

#endif //WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
