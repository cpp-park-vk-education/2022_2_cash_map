#ifndef SERVER_USER_SESSION_H
#define SERVER_USER_SESSION_H

#include <memory>
#include <queue>
#include <string>

#include <boost/beast.hpp>
#include <boost/asio.hpp>

#include "user.h"
#include "us_types.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

class shared_state;

typedef websocket::stream<beast::tcp_stream> stream;
typedef std::unique_ptr<stream> stream_ptr;
typedef std::shared_ptr<shared_state> state_ptr;
typedef std::unique_ptr<User> user_ptr;


class user_session : public std::enable_shared_from_this<user_session>{
public:
    user_session(stream_ptr&& ws, user_ptr && user, state_ptr state);
    ~user_session() = default;

    void run();
    void do_read();
    void do_close();
    void logout();
    void handle_request();
    void on_write(error_code ec);
    void send_message(const std::string& msg);

private:
    user_ptr user_;

    stream_ptr ws_;
    beast::flat_buffer buffer_;
    state_ptr state_;

    std::queue<std::string> response_q;
};

#endif //SERVER_USER_SESSION_H
