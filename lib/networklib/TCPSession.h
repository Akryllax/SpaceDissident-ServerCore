#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

class TcpSession : public std::enable_shared_from_this<TcpSession>
{
public:
  uint16_t SESSION_ID;

private:
  std::queue<std::string> incoming_messages_;
  std::queue<std::string> outgoing_messages_;

private:
  tcp::socket socket_;
  enum
  {
    max_length = 1024
  };
  std::string data_;

public:
  TcpSession(tcp::socket socket, uint16_t session_id)
      : SESSION_ID(session_id)
      , socket_(std::move(socket))
  { }

  ~TcpSession()
  {
    socket_.close();
  }

  void close()
  {
    return socket_.close();
  };

  void write_pending(){
      //TODO Implement
  };

  void read_incoming() const {
      //TODO
  };

  bool hasIncommingMessages() const
  {
    return !incoming_messages_.empty();
  }

  std::optional<std::string> popIncomingMessage()
  {
    if(incoming_messages_.empty())
    {
      return std::nullopt;
    }

    std::string message = incoming_messages_.front();
    incoming_messages_.pop();
    return message;
  }
};
