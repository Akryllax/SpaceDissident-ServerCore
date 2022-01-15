

#include "gtest/gtest.h"
#include "basic_setup.h"
#include "common/gameobject.h"

TEST(BasicVectorTest, VectorAdd)
{
    World::GameObject go;
};

int main(int argc, char **argv)
{
    spdlog_init("gameobject_gtest.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
