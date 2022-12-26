#include "ws_session.hpp"
#include "serializer.h"
#include "viewer_manager.hpp"
#include "user_session.h"
#include "user_creator.h"
#include "DB.h"


#include "ps_types.hpp"

ws_session::ws_session(tcp::socket &&socket, state_ptr state):
        ws_(std::make_unique<stream>(std::move(socket))),
        state_(std::move(state))
{}

ws_session::ws_session(stream_ptr &&ws, state_ptr state):
    ws_(std::move(ws)), 
    state_(std::move(state))
{}


void ws_session::run(){
    std::cout << "[ws run]" << std::endl;
    ws_->async_accept([self{shared_from_this()}](error_code ec){
        if(ec){
            std::cout << "[ws accepted] " << ec.message() << std::endl;
        }
        self->do_read();
    });
}

void ws_session::do_read() {
    ws_->async_read(buffer_,
    [self{shared_from_this()}](error_code ec, std::size_t){
        if(ec && ec != boost::asio::error::eof){
            std::cout << "[ws async read error]" << ec.message() <<  std::endl;
            return;
        }
        self->handle_request();
    });
}


void ws_session::do_close(){
    ws_->close("");
}

void ws_session::on_write(error_code ec) {
    if(ec){
        std::cout << "[ws_session write error] " << ec.message() << std::endl;
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

void ws_session::handle_request(){
    std::cout << "[ws_session handle request]" << std::endl;
    try {
        auto req = serializer::deserialize(beast::buffers_to_string(buffer_.data()));
        std::cout << beast::buffers_to_string(buffer_.data()) << std::endl;
        buffer_.consume(buffer_.size());
        auto t = ps_types.at(req["type"]);
        switch (t) {
            case ps_type::login:
            {
                // TODO normal db client
                auto user = DB::get_instance().get_user_by_id(req["login"], req["password"]);
                if (!user){
                    auto msg = response_creator::create_with_status("login", 403);
                    send_msg(msg);
                    break;
                }
                user_creator::create(std::move(ws_), std::move(user), state_)->run();
                return;
            }
            case ps_type::reg:
            {
                bool pass = DB::get_instance().add_user(req["nick"], req["login"], req["password"]);
                if(!pass){
                    auto msg = response_creator::create_with_status("reg", 409);
                    send_msg(msg);
                    break;
                }
                auto user = DB::get_instance().get_user_by_id(req["login"], req["password"]);
                user_creator::create(std::move(ws_), std::move(user), state_)->run();
                return;
            }
            case ps_type::join:
                std::make_shared<viewer_manager>
                (std::move(req), std::move(ws_), state_)->handle_request();
                return;
            default:
            {
                auto msg = response_creator::create_with_status("invalid", 400);
                send_msg(msg);
                return;
            }
        }
    }
    catch(...){
        auto msg = response_creator::create_with_status("invalid", 400);
        send_msg(msg);
    }
    do_read();

}

void ws_session::send_msg(const std::string &msg) {
    response_q.push(msg);
    if(response_q.size() > 1)
        return;
    ws_->async_write(net::buffer(msg),
    [self{shared_from_this()}](error_code ec, std::size_t){
        self->on_write(ec);
    });
}

