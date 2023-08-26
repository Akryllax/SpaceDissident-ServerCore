#include <stdexcept>
#include <string>

namespace NetworkLib
{
inline unsigned short convertToPort(const std::string& portStr)
{
  unsigned long portLong = std::stoul(portStr);
  if(portLong > 65535)
  {
    throw std::invalid_argument("Port number out of range");
  }
  return static_cast<unsigned short>(portLong);
};
} // namespace NetworkLib