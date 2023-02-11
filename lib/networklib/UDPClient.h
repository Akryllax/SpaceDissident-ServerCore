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
  const boost::asio::io_context& io_context_;
  const std::string& host_;
  const unsigned short port_;

public:
  static const int BUFFER_SIZE = 1024;

  UDPClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : socket_(std::make_unique<udp::socket>(io_context))
      , endpoint_(boost::asio::ip::make_address(host), std::stoul(port))
      , io_context_(io_context)
      , host_(host)
      , port_(std::stoul(port))
  { }

  ~UDPClient()
  {
    socket_->close();
  }

  void start()
  {
    // Create the socket and open it
    auto socket_ptr = std::make_unique<udp::socket>(io_context_);

    // Open the socket
    socket_ptr->open(udp::v4());

    socket_ = std::move(socket_ptr);
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

  std::string receive()
  {
    std::string response;
    udp::endpoint sender_endpoint;
    try
    {
      boost::asio::streambuf buffer;
      socket_->receive_from(buffer.prepare(BUFFER_SIZE), sender_endpoint);
      response = boost::asio::buffer_cast<const char*>(buffer.data());
    }
    catch(std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    return response;
  }
};
