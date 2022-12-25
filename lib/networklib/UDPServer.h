#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

#pragma once

using boost::asio::ip::udp;

class UDPServer
{
  friend class UDPTest;

  public:
  UDPServer(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : socket_(io_context, udp::endpoint(udp::v4(), std::stoul(port)))
      , endpoint_(boost::asio::ip::make_address(host), std::stoul(port))
      , io_context_(io_context)

  { }

  void run()
  {
    try
    {

      running = true;
      do_receive();
      io_context_.run();
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  void stop()
  {
    running = false;
    socket_.close();
  }

  std::vector<std::string> received_messages() const
  {
    return received_messages_;
  }

  private:
  void do_receive()
  {
    try
    {
      while(running)
      {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_),
                                   remote_endpoint_,
                                   [this](boost::system::error_code ec, std::size_t length) {
                                     if(!ec)
                                     {
                                       received_messages_.emplace_back(recv_buffer_.data(), length);
                                     }
                                   });
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  udp::socket socket_;
  udp::endpoint endpoint_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1024> recv_buffer_;
  std::vector<std::string> received_messages_;
  boost::asio::io_context& io_context_;
  bool running = false;
};
