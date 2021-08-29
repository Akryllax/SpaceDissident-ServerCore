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
