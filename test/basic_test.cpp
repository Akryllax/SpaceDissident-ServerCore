#include "gtest/gtest.h"
#include "base_message.h"
#include "basic_setup.h"

TEST(BasicMessageTest_CreateObject, PositiveNos){
    BaseMessage message;
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
