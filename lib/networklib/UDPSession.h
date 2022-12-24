#include <boost/asio.hpp>

using boost::asio::ip::udp;

class Session {
public:
  Session(udp::socket& socket, udp::endpoint& endpoint)
      : socket_(socket),
        endpoint_(endpoint)
  {
  }

  void Start()
  {
    // Begin receiving data from the client
    do_receive();
  }

private:
  void do_receive()
  {
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t length) {
          if (!ec && length > 0) {
            // Process the data and send a response
            do_send(length);
          } else {
            // Close the session
            delete this;
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

  udp::socket& socket_;
  udp::endpoint& endpoint_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
};