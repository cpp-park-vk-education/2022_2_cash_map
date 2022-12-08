#include "viewer.h"

#include <utility>

#include "handler.h"

Viewer::Viewer(stream_ptr &&ws, uuid&& id, room_ptr&& room):
        id_(std::forward<uuid>(id)),
        room_(std::move(room)),
        ws_(std::move(ws))
{}

Viewer::~Viewer(){
    std::cout << "[viewer destructor]\n";
    room_->leave(id_);
}


void Viewer::start() {
    room_->join(shared_from_this()->weak_from_this());
    do_read();
}

void Viewer::pause() {

}

void Viewer::play() {

}

void Viewer::rewind(int) {

}


void Viewer::send_chat_msg(std::string) {

}


void Viewer::do_read() {
    ws_->async_read(buffer_,
    [self{shared_from_this()}](error_code ec, std::size_t bytes_read){
        if(ec){
            std::cout << "[viewer async read] " << ec.message() <<  std::endl;
            return;
        }
        auto in = beast::buffers_to_string(self->buffer_.cdata());
        self->buffer_.consume(bytes_read);
        std::cout << "[viewer handle] " <<  in << std::endl;
        self->do_read();
        std::make_unique<handler>(std::move(in), self->shared_from_this(), self->room_)->handle_request();
    });
}


uuid Viewer::get_id() const {
    return id_;
}


std::string Viewer::get_nickname() const {
    return nickname_;
}

void Viewer::set_nickname(std::string nickname) {
    nickname_ = nickname;
}

void Viewer::set_room(const room_ptr &room) {
    room_ = room;
}


void Viewer::set_access_opts(const access_options& opts) {
    a_opts_ = opts;
}

void Viewer::set_timestamp() {

}

access_options Viewer::get_a_opts() const {
    return a_opts_;
}

void Viewer::do_close() {
    ws_->close("");
}

void Viewer::send_response(const std::string &) {

}


Host::Host(stream_ptr &&stream, uuid&& id): Viewer(std::move(stream), std::forward<uuid>(id))
{}

void Host::synchronize() {

}

void Host::change_access_opts() {

}
