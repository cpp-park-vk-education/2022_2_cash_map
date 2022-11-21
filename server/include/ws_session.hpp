#ifndef WATCH_UP_PROJECT_WS_SESSION_HPP
#define WATCH_UP_PROJECT_WS_SESSION_HPP

#include <memory>

#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;

class WS_Session : std::enable_shared_from_this<WS_Session> {
public:
    void run();
    void on_run();
    void on_accept();
    void on_read();
    void handle_request();

private:
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;

};


#endif //WATCH_UP_PROJECT_WS_SESSION_HPP


