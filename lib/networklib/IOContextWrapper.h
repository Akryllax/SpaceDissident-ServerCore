#pragma once

#include "boost/asio.hpp"

namespace NetworkCore
{
class ServerIoContextWrapper
{
private:
  static inline boost::asio::io_context io_context_;

public:
  static boost::asio::io_context& getInstance()
  {
    return io_context_;
  }
};

class ClientIoContextWrapper
{
private:
  static inline boost::asio::io_context io_context_;

public:
  static boost::asio::io_context& getInstance()
  {
    return io_context_;
  }
};
} // namespace NetworkCore
