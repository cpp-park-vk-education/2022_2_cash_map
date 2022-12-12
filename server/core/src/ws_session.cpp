#include "ws_session.hpp"

#include "viewer_manager.hpp"

ws_session::ws_session(tcp::socket &&socket, state_ptr state):
        ws_(std::make_unique<stream>(std::move(socket))),
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
        auto in = beast::buffers_to_string(self->buffer_.cdata());
        self->handle_request();
    });
}


void ws_session::do_close(){
    ws_->close("");
}

void ws_session::handle_request(){
    std::cout << "[handle request]" << std::endl;

    std::make_unique<viewer_manager>
    (beast::buffers_to_string(buffer_.data()), std::move(ws_), state_)->handle_request();
}
