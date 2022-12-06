#ifndef WATCH_UP_PROJECT_WS_SESSION_HPP
#define WATCH_UP_PROJECT_WS_SESSION_HPP
#include <iostream>
#include <memory>

#include <boost/beast.hpp>
#include <boost/asio.hpp>

#include "shared_state.h"
#include "serializer.h"
#include "viewer.h"
#include "room.h"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

typedef websocket::stream<beast::tcp_stream> stream;
typedef std::unique_ptr<stream> stream_ptr;
typedef std::shared_ptr<shared_state> state_ptr;


class ws_session : public std::enable_shared_from_this<ws_session> {
public:
    // TODO rm virtual
    ws_session(tcp::socket &&socket, state_ptr state);
    virtual ~ws_session() = default;

    virtual void run();
    virtual void do_read();
    virtual void do_close();
    virtual void handle_request();

protected:
    stream_ptr ws_;
    beast::flat_buffer buffer_;
    state_ptr state_;
};


#endif //WATCH_UP_PROJECT_WS_SESSION_HPP


