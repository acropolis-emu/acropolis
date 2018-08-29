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
#include <necv60/registers.h>

TEST(ComputeFlags, TestPSW) {
  Registers registers{};
  auto &psw = static_cast<uint32_t &>(registers.psw);

  psw = 0x00000001;

  EXPECT_EQ(0x00000001, static_cast<uint32_t &>(registers.psw));
  EXPECT_EQ(0x00000001, registers.psw.value);
  EXPECT_EQ(1, registers.psw.z);

  psw = 0x00010000;

  EXPECT_EQ(0x00010000, static_cast<uint32_t &>(registers.psw));
  EXPECT_EQ(0x00010000, registers.psw.value);
  EXPECT_EQ(1, registers.psw.te);

}
