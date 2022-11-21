#ifndef WATCH_UP_PROJECT_LISTENER_H
#define WATCH_UP_PROJECT_LISTENER_H

#include <memory>

#include <boost/beast/core.hpp>

#include "shared_state.h"

class Listener: public std::enable_shared_from_this<Listener>{
public:
    Listener(boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint endpoint);
    ~Listener();

    void async_accept();
    void on_accept();

private:
    Shared_state state_;
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

};

#endif //WATCH_UP_PROJECT_LISTENER_H
