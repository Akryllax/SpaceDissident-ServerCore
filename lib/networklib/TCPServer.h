#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "TCPSession.h"

#pragma once

using boost::asio::ip::tcp;

class TCPServer {

  friend class asio_udp_test;

public:
  TCPServer(boost::asio::io_context& io_context, const std::string& port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), stoi(port))),
        socket_(io_context)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
      if (!ec) {
        std::make_shared<TcpSession>(std::move(socket_))->start();
      }

      do_accept();
    });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};