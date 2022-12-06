#ifndef WATCH_UP_PROJECT_LISTENER_H
#define WATCH_UP_PROJECT_LISTENER_H

#include <memory>

#include <boost/beast/core.hpp>

#include "shared_state.h"

typedef std::shared_ptr<shared_state> state_ptr;

class listener: public std::enable_shared_from_this<listener>{
public:
    listener(boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint&& endpoint);
    ~listener();

    void async_accept();
    void on_accept(boost::system::error_code& ec);

private:
    state_ptr state_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

};

#endif //WATCH_UP_PROJECT_LISTENER_H
