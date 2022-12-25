#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPClient {
public:
  TCPClient(boost::asio::io_context& io_context,
         const std::string& host,
         const std::string& port)
      : resolver_(io_context),
        socket_(io_context)
  {
    tcp::resolver::results_type endpoints = resolver_.resolve(host, port);
    do_connect(endpoints);
  }

  void write(const std::string& message)
  {
    boost::asio::async_write(socket_, boost::asio::buffer(message),
                              [](boost::system::error_code /*ec*/, std::size_t /*length*/) {});
  }

private:
  void do_connect(tcp::resolver::results_type endpoints)
  {
    boost::asio::async_connect(socket_, endpoints,
                               [this](boost::system::error_code ec, tcp::endpoint) {
                                 if (!ec) {
                                   do_read();
                                 }
                               });
  }

  void do_read()
  {
    boost::asio::async_read(socket_, boost::asio::buffer(data_, max_length),
                            [this](boost::system::error_code ec, std::size_t length) {
                              if (!ec) {
                                std::cout << std::string(data_, length) << std::endl;
                                do_read();
                              }
                            });
  }

  tcp::resolver resolver_;
  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};