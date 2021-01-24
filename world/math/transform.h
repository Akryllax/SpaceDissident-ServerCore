#include "Vector3.h"
#include "Matrix4.h"

namespace World
{
    struct Transform
    {
        World::Vector3 position;
        World::Matrix4 rotation;
        World::Vector3 scale;
    };
} // namespace World