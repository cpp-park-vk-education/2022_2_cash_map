#include "session.h"

session::session(tcp::socket &&socket)
{}
session::session(stream_ptr&& ws){}


void session::run(){

}
void session::do_read(){

}
void session::do_close(){

}
void session::handle_request(){

}
void session::send_msg(const std::string& msg){

}
void session::on_write(error_code ec){

}

