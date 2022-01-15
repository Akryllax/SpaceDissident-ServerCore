

#include "gtest/gtest.h"
#include "basic_setup.h"
#include "common/data_holder.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Color.h"
#include "math/Matrix3.h"
#include "math/Matrix4.h"
#include "math/transform.h"
#include "test_library.h"

TEST(BasicVectorTest, VectorAdd)
{
    World::Vector3 vecA = {0, 1, 2};
    World::Vector3 vecB = {3, 2, 1};
    World::Vector3 vecUnitary = {1, 1, 1};

    ASSERT_EQ(World::Vector3(3, 3, 3), vecA + vecB);
    ASSERT_EQ(World::Vector3(4,4,4), vecUnitary * 4);

    auto t = new TestLibrary();
    TestLibrary::helloStatic();
};

int main(int argc, char **argv)
{
    spdlog_init("world_gen_test.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
