#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class UDPServer {
public:
  UDPServer(boost::asio::io_context& io_context, short port)
      : socket_(io_context, udp::endpoint(udp::v4(), port))
  {
    do_receive();
  }

private:
  void do_receive()
  {
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t length) {
          if (!ec && length > 0) {
            do_send(length);
          } else {
            do_receive();
          }
        });
  }

  void do_send(std::size_t length)
  {
    socket_.async_send_to(boost::asio::buffer(data_, length), sender_endpoint_,
                         [this](boost::system::error_code /*ec*/, std::size_t /*length*/) {
                           do_receive();
                         });
  }

  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};