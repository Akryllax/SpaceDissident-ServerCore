#include <memory>
#include "gtest/gtest.h"
#include "basic_setup.h"
#include "server_core.h"
#include "modules/test_core_module.h"

TEST(NetworkLibTest, FakeTest)
{
    auto serverCoreInstance = std::unique_ptr<ServerCore>();

    serverCoreInstance->initialize();
    serverCoreInstance->tick();
};

int main(int argc, char **argv)
{
    spdlog_init("server_core_test.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
