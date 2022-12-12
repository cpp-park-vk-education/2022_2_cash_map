#ifndef WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
#define WATCH_UP_PROJECT_VIEWER_MANAGER_HPP

#include <string>
#include <utility>
#include <unordered_map>

#include <boost/beast.hpp>

#include "types.hpp"
#include "serializer.h"
#include "viewer_creator.hpp"
#include "room_creator.hpp"
#include "response_creator.hpp"

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
        str_req_(std::move(ws_req))
    {}

    void do_close(){
        //TODO log close reason
        ws_->close("");
    }

    void define_type(){
        auto it = types.find(req_["type"]);
        if(it == types.end())
            return;
        type_ = it->second;
    }

    void handle_request(){
        try {
            req_ = serializer::deserialize(str_req_);

            define_type();
            std::cout << str_req_ << std::endl;
            if (type_ == create) {
                //auto nickname = req_["nick"];
                auto host = viewer_creator::create_host(std::move(ws_), "blank");
                auto room = room_creator::create_room(std::weak_ptr(host), state_);


                state_->add_room(room->get_id(), std::weak_ptr(room));
                host->set_room(room);
                host->start();
                room->start();

            } else if (type_ == join) {
                auto room_id = boost::lexical_cast<uuid>(req_["room_id"]);
                //auto nickname = req_["nick"];
                auto room = state_->get_room(room_id);
                if (!room.lock()) {
                    //ws_->async_write("not found");
                    return;
                }
                viewer_creator::create_viewer(std::move(ws_), "blank", room.lock())->start();
            } else if (type_ == invalid) {
                ws_->async_write(net::buffer("bad request"),
                                 [](error_code , std::size_t){
                                     std::cout << "send\n";
                });
                return;
            } else {
                // TODO send method not allowed
                ws_->async_write(net::buffer("not allowed"),
                [](error_code , std::size_t){
                        std::cout << "send\n";
                });
            }
        }
        catch (nlohmann::json::exception& ec){
            std::cout << ec.what();
            return;
        }
    }
private:
    stream_ptr ws_;
    state_ptr state_;

    type type_ = invalid;

    std::string str_req_;
    std::unordered_map<std::string, std::string> req_;

};

#endif //WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
