#include "viewer.h"

#include <utility>

#include "handler.h"

Viewer::Viewer(stream_ptr &&ws, uuid&& id, room_ptr&& room):
        id_(std::forward<uuid>(id)),
        room_(std::move(room)),
        ws_(std::move(ws))
{}

Viewer::Viewer(stream_ptr &&ws, uuid &&id, access_options a_opts, room_ptr&& room):
        id_(std::forward<uuid>(id)),
        room_(std::move(room)),
        a_opts_(a_opts),
        ws_(std::move(ws))
{}

Viewer::~Viewer(){
    std::cout << "[viewer destructor]\n";
    room_->leave(id_, nickname_);
}


void Viewer::start() {

    room_->join(shared_from_this()->weak_from_this());
    do_read();
}

void Viewer::do_read() {
    ws_->async_read(buffer_,
    [self{shared_from_this()}](error_code ec, std::size_t ){
        if(ec){
            std::cout << "[viewer async read] " << ec.message() <<  std::endl;
            return;
        }
        auto in = beast::buffers_to_string(self->buffer_.cdata());
        self->buffer_.consume(self->buffer_.size());
        std::cout << "[viewer handle] " <<  in << std::endl;
        self->do_read();
        std::make_unique<handler>(std::move(in), self->shared_from_this(), self->room_)->handle_request();
    });
}


void Viewer::do_close() {
    ws_->close("");
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
        std::cout << "viewer write error: " << ec.message() << std::endl;
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

uuid Viewer::get_id() const {
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
