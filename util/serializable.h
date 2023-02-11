#include <string>
#include <type_traits>

class ISerializable
{
public:
  long UQ_ID;

public:
  virtual std::string toString(){};

  // public:
  // template<typename T>
  // static T* fromString(std::string serialized) {};
};