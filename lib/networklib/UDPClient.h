#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::udp;

class UDPClient {
public:
  UDPClient(boost::asio::io_context &io_context, const std::string &host,
            const std::string &port)
      : socket_(io_context),
        endpoint_(boost::asio::ip::make_address(host), std::stoul(port)) {}

  void write(const std::string &message) {
    socket_.async_send_to(
        boost::asio::buffer(message), endpoint_,
        [](boost::system::error_code /*ec*/, std::size_t /*length*/) {});
  }

private:
  udp::socket socket_;
  udp::endpoint endpoint_;
};