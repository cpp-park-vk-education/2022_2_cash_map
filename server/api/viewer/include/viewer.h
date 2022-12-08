#ifndef WATCH_UP_PROJECT_VIEWER_H
#define WATCH_UP_PROJECT_VIEWER_H

#include <iostream>
#include <string>
#include <memory>
#include <queue>

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>

#include "room.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;
using uuid = boost::uuids::uuid;

typedef std::shared_ptr<IRoom> room_ptr;
typedef websocket::stream<beast::tcp_stream> ws_stream;
typedef std::unique_ptr<ws_stream> stream_ptr;

class handler;

struct access_options{
    bool can_pause;
    bool can_rewind;
    bool is_host;
};


class IViewer{
public:
    virtual ~IViewer()                                      = default;
    virtual void start()                                    = 0;
    virtual void pause()                                    = 0;
    virtual void play()                                     = 0;
    virtual void rewind(int offset)                         = 0;
    virtual void set_timestamp()                            = 0;
    virtual void send_chat_msg(std::string msg)             = 0;

    virtual void do_read()                                  = 0;
    virtual void do_close()                                 = 0;
    virtual void send_response(const std::string&)          = 0;

    virtual uuid get_id() const                             = 0;
    virtual std::string get_nickname() const                = 0;
    virtual access_options get_a_opts() const               = 0;

    virtual void set_nickname(std::string)                  = 0;
    virtual void set_room(const room_ptr& room)             = 0;
    virtual void set_access_opts(const access_options& opts)= 0;


};

class Viewer: public IViewer, public std::enable_shared_from_this<Viewer> {
public:
    Viewer(stream_ptr && ws, uuid&& id, room_ptr&& room = nullptr);
    ~Viewer()                                   override;

    void start()                                override;
    void pause()                                override;
    void play()                                 override;
    void rewind(int )                           override;
    void set_timestamp()                        override;
    void send_chat_msg(std::string )            override;

    void do_read()                              override;
    void do_close()                             override;
    void send_response(const std::string&)      override;

    uuid get_id() const                         override;
    std::string get_nickname() const            override;
    access_options get_a_opts() const           override;

    void set_nickname(std::string)              override;
    void set_room(const room_ptr& room)         override;
    void set_access_opts(const access_options& )override;

protected:
    bool is_host;
    uuid id_;
    room_ptr room_;
    std::string nickname_;
    access_options a_opts_{};

    stream_ptr ws_;
    beast::flat_buffer buffer_;

    std::queue<std::string> response_q;
};

#endif //WATCH_UP_PROJECT_VIEWER_H


