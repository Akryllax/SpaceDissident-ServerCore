#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/streambuf.hpp>
#include <iostream>
#include <memory>
#include <string>

#pragma once

using boost::asio::ip::udp;

class UDPClient
{
public:
  static constexpr int BUFFER_SIZE = 1024;

private:
  std::unique_ptr<udp::socket> socket_;
  udp::endpoint endpoint_;
  boost::asio::io_context& io_context_;

public:
  UDPClient(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
      : io_context_(io_context)
      , endpoint_(boost::asio::ip::make_address(host), std::stoul(port))
  {
    socket_ = std::make_unique<udp::socket>(io_context_);
    socket_->open(udp::v4());
  }

  ~UDPClient()
  {
    socket_->close();
  }

  void write_async(const std::string& message)
  {
    socket_->async_send_to(
        boost::asio::buffer(message), endpoint_,
        [](boost::system::error_code ec, std::size_t /*length*/) {
          if (ec)
          {
            std::cerr << "Async write error: " << ec.message() << std::endl;
          }
        });
  }

  void write(const std::string& message)
  {
    boost::system::error_code ec;
    socket_->send_to(boost::asio::buffer(message), endpoint_, 0, ec);
    if (ec)
    {
      std::cerr << "Sync write error: " << ec.message() << std::endl;
    }
  }

  std::string receive()
  {
    udp::endpoint sender_endpoint;
    boost::asio::streambuf buffer;
    boost::system::error_code ec;
    socket_->receive_from(buffer.prepare(BUFFER_SIZE), sender_endpoint, 0, ec);
    buffer.commit(BUFFER_SIZE);

    if (ec)
    {
      std::cerr << "Receive error: " << ec.message() << std::endl;
      return "";
    }

    return boost::asio::buffer_cast<const char*>(buffer.data());
  }
};
