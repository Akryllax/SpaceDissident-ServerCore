#include <algorithm>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <memory>
#include <string>

#pragma once

using boost::asio::ip::udp;

class UDPClient
{

  private:
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint endpoint_;
  boost::asio::io_context& io_context_;
  const std::string& host_;
  const unsigned long port_;

  public:
  UDPClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : socket_(std::make_unique<udp::socket>(io_context))
      , endpoint_(boost::asio::ip::make_address(host), std::stoul(port))
      , host_(host)
      , port_(std::stoul(port))
      , io_context_(io_context)
  { }

  void start()
  {
    // Create the socket and open it
    socket_ = std::make_unique<udp::socket>(io_context_, udp::v4());

    // Set the endpoint for the socket
    udp::endpoint endpoint_(boost::asio::ip::make_address(host_), port_);

    // Bind the socket to the endpoint
    // socket_->bind(endpoint_);
  }

  void write_async(const std::string& message)
  {
    socket_->async_send_to(boost::asio::buffer(message),
                           endpoint_,
                           [](boost::system::error_code /*ec*/, std::size_t /*length*/) {});
  }

  void write(const std::string& message)
  {
    boost::system::error_code ec;
    socket_->send_to(boost::asio::buffer(message), endpoint_, 0, ec);
    if(ec)
    {
      // Handle error here
      std::cerr << "Errored: " << ec.message() << std::endl;
    }
  }
};
