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
#include "basic_setup.h"

TEST(BasicMessageTest_CreateObject, BasicMessage_addDecoratorBasic)
{
    auto *message = new BaseMessage();
    ASSERT_NE(nullptr, message);

    ASSERT_TRUE(message->addDecorator<BaseDecorator>());
    ASSERT_EQ(1, message->getDecoratorCount());
};

TEST(BasicMessageTest_CreateObject, BasicMessage_getDecorator)
{
    auto *message = new BaseMessage();
    ASSERT_NE(nullptr, message);

    ASSERT_TRUE(message->addDecorator<BaseDecorator>());
    ASSERT_NE(nullptr, message->getDecorator<BaseDecorator>());
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
