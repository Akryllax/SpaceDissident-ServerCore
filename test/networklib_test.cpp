#include "gtest/gtest.h"
#include "basic_setup.h"
#include "networklib.h"

TEST(NetworkLibTest, FakeTest)
{
    auto *itf = new NetworkShared::NetworkInterface();
    GTEST_ASSERT_EQ(5, itf->testFunction());
    delete itf;
};

int main(int argc, char **argv)
{
    basic_setup("world_gen_test.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
