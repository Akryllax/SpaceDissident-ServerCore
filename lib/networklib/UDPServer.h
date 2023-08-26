#pragma once

#include "INetworkChannel.h"
#include "IOContextWrapper.h"
#include <array>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>
#include "NetworkUtils.h"

using boost::asio::ip::udp;

class UDPServer : public INetworkChannel
{
public:
  UDPServer(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : socket_(io_context, udp::endpoint(udp::v4(), NetworkLib::convertToPort(port)))
      , endpoint_(boost::asio::ip::make_address(host), NetworkLib::convertToPort(port))
      , io_context_(io_context)
  { }

  UDPServer(const std::string& host, const std::string& port)
      : socket_(NetworkCore::IoContextWrapper::getInstance(),
                udp::endpoint(udp::v4(), NetworkLib::convertToPort(port)))
      , endpoint_(boost::asio::ip::make_address(host), NetworkLib::convertToPort(port))
      , io_context_(NetworkCore::IoContextWrapper::getInstance())
  { }

  void run()
  {
    running = true;
    do_receive();
    io_context_.run();
  }

  void stop()
  {
    running = false;
    socket_.close();
  }

  std::vector<std::string> received_messages() const
  {
    std::lock_guard lock(mutex_);
    return received_messages_;
  }

  // INetworkChannel methods
  bool isOpen() const override
  {
    return running;
  }
  bool write(const std::string& data) override
  {
    boost::system::error_code ec;
    socket_.send_to(boost::asio::buffer(data), endpoint_, 0, ec);
    return !ec; // return true if no error occurred
  }
  std::vector<std::string> read() override
  {
    std::lock_guard lock(mutex_);
    auto messages = received_messages_;
    received_messages_.clear();
    return messages;
  }
  void close() override
  {
    stop();
    io_context_.stop();
  }

private:
  void do_receive()
  {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_),
                               remote_endpoint_,
                               [this](boost::system::error_code ec, std::size_t length) {
                                 if(!ec)
                                 {
                                   std::lock_guard lock(mutex_);
                                   received_messages_.emplace_back(recv_buffer_.data(), length);
                                   if(running)
                                     do_receive();
                                 }
                               });
  }

  udp::socket socket_;
  udp::endpoint endpoint_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1024> recv_buffer_;
  mutable std::mutex mutex_;
  std::vector<std::string> received_messages_;
  boost::asio::io_context& io_context_;
  bool running = false;
};
