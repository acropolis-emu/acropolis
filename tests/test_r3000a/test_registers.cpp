/*
 *  Acropolis  Copyright (C) 2018 Team Acropolis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <r3000a/registers.h>

TEST(Registers, TestAlias) {
  Registers registers{};

  registers.set(1, 0x10);
  EXPECT_EQ(registers.at, 0x10);

  registers.at = 0x20;
  EXPECT_EQ(registers.get(1), 0x20);
}

TEST(Registers, TestZeroRegister) {
  Registers registers{};
  registers.set(0, 0x10);
  EXPECT_EQ(registers.zr, 0x00);
  EXPECT_EQ(registers.get(0), 0x00);
}
