#include "viewer.h"

#include <utility>


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
                    [self{shared_from_this()}](error_code ec, std::size_t){
                        if(ec){
                            std::cout << "[viewer async read] " << ec.message() <<  std::endl;
                            return;
                        }
                        auto in = beast::buffers_to_string(self->buffer_.cdata());
                        std::cout << "[viewer handle] " <<  in << std::endl;
                        self->do_read();
                    });

}


uuid Viewer::get_id() const {
    return id_;
}


std::string Viewer::get_nickname() const {
    return std::string();
}

void Viewer::set_nickname(std::string) {

}

void Viewer::set_room(const room_ptr &room) {
    room_ = room;
}


void Viewer::set_access_opts(access_options) {

}


Host::Host(stream_ptr &&stream, uuid&& id): Viewer(std::move(stream), std::forward<uuid>(id))
{}

void Host::synchronize() {

}

void Host::change_access_opts() {

}
