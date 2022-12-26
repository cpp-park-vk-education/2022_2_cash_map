#include "viewer.h"

#include <utility>

#include "handler.h"
#include "ws_session.hpp"
#include "user_session.h"

Viewer::Viewer(stream_ptr &&ws, user_ptr&& user, room_ptr&& room):
        user_(std::move(user)),
        room_(std::move(room)),
        ws_(std::move(ws))
{
    id_ = user_->get_id();
    nickname_ = user_->get_nick();
}

Viewer::Viewer(stream_ptr &&ws, access_options a_opts, user_ptr&& user, room_ptr&& room):
        user_(std::move(user)),
        room_(std::move(room)),
        ws_(std::move(ws)),

        a_opts_(a_opts)
{
    id_ = user_->get_id();
    nickname_ = user_->get_nick();
}

Viewer::Viewer(stream_ptr &&ws, std::string &&id, std::string &&nick, room_ptr&& room) :
    id_(id),
    nickname_(std::move(nick)),

    user_(user_ptr(nullptr)),
    room_(std::move(room)),
    ws_(std::move(ws))
{}

Viewer::~Viewer(){
    std::cout << "[viewer destructor]\n";
    if(room_)
        room_->leave(id_, nickname_);
}


void Viewer::start() {
    room_->join(shared_from_this()->weak_from_this());
    do_read();
}

void Viewer::do_read() {
    ws_->async_read(buffer_,
    // expands the lifetime of viewer instance
    [self{shared_from_this()}](error_code ec, std::size_t ){
        if(ec && ec != boost::asio::error::eof){
            std::cout << "[viewer async read error] " << ec.message() <<  std::endl;
            return;
        }
        auto in = beast::buffers_to_string(self->buffer_.cdata());
        self->buffer_.consume(self->buffer_.size());
        // creates an event loop
        handler(std::move(in), self->shared_from_this(), self->room_).handle_request();
    });
}


void Viewer::do_close() {
    if(user_){
        std::make_shared<user_session>(std::move(ws_), std::move(user_), room_->get_state())->do_read();
        return;
    }
    std::make_shared<ws_session>(std::move(ws_), room_->get_state())->do_read();
}

void Viewer::send_message(const std::string & msg) {
    response_q.push(msg);
    if(response_q.size() > 1)
        return;
    ws_->async_write(net::buffer(msg),
    [self{shared_from_this()}](error_code ec, std::size_t){
        self->on_write(ec);
    });
}

void Viewer::on_write(error_code ec) {
    if(ec){
        std::cout << "[viewer write error] " << ec.message() << std::endl;
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

std::string Viewer::get_id() const {
    return id_;
}


std::string Viewer::get_nickname() const {
    return nickname_;
}

access_options Viewer::get_a_opts() const {
    return a_opts_;
}

void Viewer::set_nickname(std::string nickname) {
    nickname_ = nickname;
}

void Viewer::set_room(const room_ptr &room) {
    room_ = room;
}

void Viewer::set_access_opts(const access_options& opts) {
    a_opts_ = opts;
    std::cout << "can pause " << a_opts_.can_pause << std::endl;
}
