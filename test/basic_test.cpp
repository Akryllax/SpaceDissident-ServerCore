/*
 *   Copyright (c) 2021 Akryllax (akryllax@gmail.com)

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "base_message.h"
#include "base_decorator.h"
#include "debug_decorator.h"
#include "basic_setup.h"

TEST(BasicMessageTest, addDecoratorBasic)
{
    auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
    ASSERT_NE(nullptr, message);

    ASSERT_TRUE(message->addDecorator<BaseDecorator>());
    ASSERT_EQ(1, message->getDecoratorCount());
    ASSERT_FALSE(message->addDecorator<BaseDecorator>());
};

TEST(BasicMessageTest, getDecorator)
{
    auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
    ASSERT_NE(nullptr, message);

    ASSERT_TRUE(message->addDecorator<BaseDecorator>());
    ASSERT_NE(nullptr, message->getDecorator<BaseDecorator>());
};

TEST(BasicMessageTest, addGetDebugDecorator)
{
    auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
    ASSERT_NE(nullptr, message);

    ASSERT_TRUE(message->addDecorator<DebugDecorator>());
    ASSERT_NE(nullptr, message->getDecorator<DebugDecorator>());
};

TEST(DebugDecoTest, to_string)
{
    auto debugDeco = std::unique_ptr<DebugDecorator>(new DebugDecorator);

    ASSERT_EQ("DebugDecorator", debugDeco->to_string());
};

TEST(DecoTest, searchDecoBasic_1)
{
    auto *message = new BaseMessage();

    auto baseDeco = new BaseDecorator();
    auto debugDeco = new DebugDecorator();

    std::vector<BaseDecorator*> baseDecoList = {baseDeco, debugDeco};

    auto deco_basic = deco::search_deco<BaseDecorator>(baseDecoList);
    auto deco_debug = deco::search_deco<DebugDecorator>(baseDecoList);

    ASSERT_NE(nullptr, deco_basic);
    ASSERT_NE(nullptr, deco_debug);
    ASSERT_EQ(2, baseDecoList.size());
    ASSERT_NE(deco_basic, deco_debug);

};

int main(int argc, char **argv)
{
    basic_setup();
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
