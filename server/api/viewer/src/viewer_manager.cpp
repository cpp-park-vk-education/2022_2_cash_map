#include "viewer_manager.hpp"
#include "us_types.hpp"

viewer_manager::viewer_manager(std::string&& ws_req, stream_ptr&& ws, state_ptr state, user_ptr&& user):
    ws_(std::move(ws)),
    state_(std::move(state)),
    str_req_(std::move(ws_req)),
    user_(std::move(user))
{}

viewer_manager::viewer_manager(std::unordered_map<std::string, std::string>&& req, stream_ptr&& ws, state_ptr state, user_ptr&& user):
    ws_(std::move(ws)),
    state_(std::move(state)),
    req_(std::move(req)),
    user_(std::move(user))
{}

void viewer_manager::do_close(){
    // pass to low level
    std::make_shared<ws_session>(std::move(ws_), state_)->do_read();
}


void viewer_manager::define_type(){
    auto it = us_types.find(req_["type"]);
    if(it == us_types.end())
        return;
    type_ = it->second;
}

void viewer_manager::handle_request(){
    try {
        if (req_.empty()){
            req_ = serializer::deserialize(str_req_);
        }
        define_type();
        if (type_ == us_type::create) {
            auto host = viewer_creator::create_host(std::move(ws_), std::move(user_));
            auto room = room_creator::create_room(std::weak_ptr(host), state_);
            room->service(req_["service"]);
            state_->add_room(room->get_id(), std::weak_ptr(room));
            host->set_room(room);

            host->start();
            room->start();

        } else if (type_ == us_type::join) {
            auto room_id = boost::lexical_cast<uuid>(req_["room_id"]);
            auto room = state_->get_room(room_id);
            if (!room.lock()) {
                auto msg = response_creator::create_with_status("join", 404);
                send_message(msg);
                do_close();
                return;
            }
            if(!user_){
                viewer_creator::create_anonymous(std::move(ws_), room.lock())->start();
                return;
            }
            viewer_creator::create(std::move(ws_),std::move(user_), room.lock())->start();
        } else {
            
        }
    }
    catch (...){
        auto msg = response_creator::create_with_status(us_types_to_string.at(type_), 400);
        send_message(msg);
        do_close();
        return;
    }
}

void viewer_manager::send_message(const std::string &msg) {
    response_q.push(msg);
    if(response_q.size() > 1)
        return;
    ws_->async_write(net::buffer(msg),
    [self{shared_from_this()}](error_code ec, std::size_t){
        self->on_write(ec);
    });
}

void viewer_manager::on_write(error_code ec) {
    if(ec){
        std::cout << "[viewer manager write error] " << ec.message() << std::endl;
        return;
    }
    response_q.pop();

    if(!response_q.empty()){
        ws_->async_write(net::buffer(response_q.front()),
        [self{shared_from_this()}](error_code ec_, std::size_t){
            self->on_write(ec_);
        });
    }
}
