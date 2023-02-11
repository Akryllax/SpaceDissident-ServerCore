#include <vector>

namespace akr
{
template <typename T>
class unique_holder
{
protected:
  std::vector<T*> _items;

public:
  int add(T* item) { }
};
} // namespace akr