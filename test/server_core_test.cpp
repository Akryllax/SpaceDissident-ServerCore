#include "basic_setup.h"
#include "modules/test_core_module.h"
#include "server_core.h"
#include "gtest/gtest.h"
#include <memory>

TEST(NetworkLibTest, FakeTest)
{
  auto serverCoreInstance = std::unique_ptr<ServerCore>{new ServerCore()};

  serverCoreInstance->initialize();
  serverCoreInstance->tick();
};

TEST(BasicMessageTest, addDecoratorBasic)
{
  auto serverCoreInstance = std::unique_ptr<ServerCore>{new ServerCore()};

  serverCoreInstance->initialize();
  serverCoreInstance->tick();

  TestCoreModule testCoreModule;
};

int main(int argc, char** argv)
{
  spdlog_init("server_core_test.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
