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
  enum { max_length = 1024 };
  char data_[max_length]; // Changed from std::string to char array

public:
  TcpSession(tcp::socket socket, uint16_t session_id)
      : SESSION_ID(session_id), socket_(std::move(socket)) {}

  ~TcpSession()
  {
    socket_.close();
  }

  void close()
  {
    socket_.close();
  }

  void write_pending();
  void read_incoming();
  bool hasIncomingMessages() const;
  std::optional<std::string> popIncomingMessage();
};

// Implement write_pending and read_incoming as shown above
