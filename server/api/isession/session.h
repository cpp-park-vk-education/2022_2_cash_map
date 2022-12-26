#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H

#include <memory>
#include <queue>

#include <boost/beast.hpp>
#include <boost/asio.hpp>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

typedef websocket::stream<beast::tcp_stream> stream;
typedef std::unique_ptr<stream> stream_ptr;

class session : public std::enable_shared_from_this<session>{
public:
    session(tcp::socket &&socket);
    session(stream_ptr&& ws);

    void run();
    void do_read();
    void do_close();
    void handle_request();
    void send_msg(const std::string& msg);
    void on_write(error_code ec);
protected:
    stream_ptr ws_;
    beast::flat_buffer buffer_;

    std::queue<std::string> response_q;
};


#endif //SERVER_SESSION_H


