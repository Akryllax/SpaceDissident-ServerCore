#include "Matrix4.h"
#include "Vector3.h"

namespace World
{
struct Transform
{
  World::Vector3 position;
  World::Matrix4 rotation;
  World::Vector3 scale;
};
} // namespace World