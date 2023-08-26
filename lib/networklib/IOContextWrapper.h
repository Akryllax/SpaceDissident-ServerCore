#include "boost/asio.hpp"

namespace NetworkCore
{
class IoContextWrapper
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
