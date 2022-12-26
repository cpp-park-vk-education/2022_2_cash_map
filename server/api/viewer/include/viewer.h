#ifndef WATCH_UP_PROJECT_VIEWER_H
#define WATCH_UP_PROJECT_VIEWER_H

#include <iostream>
#include <string>
#include <memory>
#include <queue>

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "room.h"
#include "user.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;
using uuid = boost::uuids::uuid;

typedef std::shared_ptr<IRoom> room_ptr;
typedef websocket::stream<beast::tcp_stream> ws_stream;
typedef std::unique_ptr<ws_stream> stream_ptr;

typedef std::unique_ptr<User> user_ptr;
class handler;

struct access_options{
    bool can_pause  = true;
    bool can_rewind = true;
    bool is_host    = true;
};


class IViewer{
public:
    virtual ~IViewer()                                      = default;
    virtual void start()                                    = 0;


    virtual void do_read()                                  = 0;
    virtual void do_close()                                 = 0;
    virtual void send_message(const std::string&)           = 0;
    virtual void on_write(error_code ec)                    = 0;

    virtual std::string get_id() const                             = 0;
    virtual std::string get_nickname() const                = 0;
    virtual access_options get_a_opts() const               = 0;

    virtual void set_nickname(std::string)                  = 0;
    virtual void set_room(const room_ptr& room)             = 0;
    virtual void set_access_opts(const access_options& opts)= 0;


};

class Viewer: public IViewer, public std::enable_shared_from_this<Viewer> {
public:
    Viewer(stream_ptr && ws, user_ptr&& user = nullptr, room_ptr&& room = nullptr);
    Viewer(stream_ptr && ws, access_options a_opts, user_ptr&& user = nullptr, room_ptr&& room = nullptr);
    Viewer(stream_ptr&& ws, std::string&& id, std::string&& nick, room_ptr&& room = nullptr);

    ~Viewer()                                   override;

    void start()                                override;

    void do_read()                              override;
    void do_close()                             override;
    void send_message(const std::string&)       override;
    void on_write(error_code ec)                override;

    std::string get_id() const                         override;
    std::string get_nickname() const            override;
    access_options get_a_opts() const           override;

    void set_nickname(std::string)              override;
    void set_room(const room_ptr& room)         override;
    void set_access_opts(const access_options& )override;

protected:
    std::string id_;
    std::unique_ptr<User> user_;
    room_ptr room_;

    std::string nickname_;
    access_options a_opts_;

    stream_ptr ws_;
    beast::flat_buffer buffer_;
    std::queue<std::string> response_q;
};

#endif //WATCH_UP_PROJECT_VIEWER_H


