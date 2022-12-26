#include "user_session.h"
#include "ws_session.hpp"
#include "serializer.h"
#include "response_creator.hpp"
#include "viewer_manager.hpp"

#include <iostream>

user_session::user_session(stream_ptr &&ws, user_ptr &&user, state_ptr state) :
        ws_(std::move(ws)),
        user_(std::move(user)),
        state_(std::move(state)) {}

void user_session::run() {
    std::cout << "[user run]\n";
    auto msg = response_creator::create_login("login", 200, user_->get_id(), user_->get_nick(), user_->get_pass());
    send_message(msg);
    do_read();
}

void user_session::do_read() {
    ws_->async_read(buffer_,
    [self{shared_from_this()}](error_code ec, std::size_t) {
        if (ec && ec != boost::asio::error::eof) {
            std::cout << "[us async read error]" << ec.message() << std::endl;
            return;
        }
        self->handle_request();
    });
}

void user_session::handle_request() {
    std::cout << "[user session handle request]\n";
    try{
        auto req = serializer::deserialize(beast::buffers_to_string(buffer_.data()));
        std::cout << beast::buffers_to_string(buffer_.data()) << std::endl;
        auto t = us_types.at(req["type"]);
        switch(t){
            case us_type::create:
            case us_type::join:{
                std::make_shared<viewer_manager>
                (std::move(req), std::move(ws_), state_, std::move(user_))->handle_request();
                return;
            }
            case us_type::logout:
                logout();
                return;
            default:
            {
                auto msg = response_creator::create_with_status(req["type"], 405);
                send_message(msg);
            }
        }
    }
    catch(...){
        auto msg = response_creator::create_with_status("invalid", 400);
        send_message(msg);

    }
    do_read();
}

void user_session::on_write(error_code ec) {
    if(ec){
        std::cout << "[user write error] " << ec.message() << std::endl;
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

void user_session::do_close() {
    ws_->close("");
}

void user_session::logout() {
    auto session = std::make_shared<ws_session>(std::move(ws_), state_);
    session->do_read();
    auto msg = response_creator::create_with_status("logout", 200);
    session->send_msg(msg);
}

void user_session::send_message(const std::string& msg){
    response_q.push(msg);
    if(response_q.size() > 1)
        return;
    ws_->async_write(net::buffer(msg),
    [self{shared_from_this()}](error_code ec, std::size_t){
        self->on_write(ec);
    });
}