#ifndef WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
#define WATCH_UP_PROJECT_VIEWER_MANAGER_HPP

#include <string>
#include <utility>
#include <unordered_map>

#include <boost/beast.hpp>

#include "us_types.hpp"
#include "serializer.h"
#include "viewer_creator.hpp"
#include "room_creator.hpp"
#include "response_creator.hpp"
#include "ws_session.hpp"


namespace beast = boost::beast;
namespace websocket = beast::websocket;

typedef websocket::stream<beast::tcp_stream> stream;
typedef std::unique_ptr<stream> stream_ptr;

class viewer_manager: public std::enable_shared_from_this<viewer_manager> {
public:
    viewer_manager() = delete;
    viewer_manager(std::string&& ws_req, stream_ptr&& ws, state_ptr state, user_ptr&& user = nullptr);
    viewer_manager(std::unordered_map<std::string, std::string>&& req, stream_ptr&& ws, state_ptr state, user_ptr&& user = nullptr);

    void do_close();
    void handle_request();
    void send_message(const std::string& msg);
    void on_write(error_code ec);
    void define_type();



private:
    stream_ptr ws_;
    state_ptr state_;
    std::queue<std::string> response_q;

    user_ptr user_;
    us_type type_ = us_type::invalid;

    std::string str_req_;
    std::unordered_map<std::string, std::string> req_;

};

#endif //WATCH_UP_PROJECT_VIEWER_MANAGER_HPP
