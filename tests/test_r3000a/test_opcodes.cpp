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
#include <r3000a/cpu.h>
#include <memory.h>
#include <unitypes.h>
#include <hdf5_hl.h>

using ::testing::Return;
using ::testing::_;

// ADDU Tests
TEST(OpCodes, ADDU) {
  PSXMemory memory{};
  R3000A cpu(&memory);

  cpu.instruction = 0x00221821;  // ADD r3, r1, r2
  cpu.registers.set(1, 0x100);
  cpu.registers.set(2, 0x200);
  cpu.registers.set(3, 0x000);

  cpu.dispatch();

  EXPECT_EQ(cpu.registers.get(1), 0x100);
  EXPECT_EQ(cpu.registers.get(2), 0x200);
  EXPECT_EQ(cpu.registers.get(3), 0x300);
}

// ADD tests
TEST(OpCodes, ADDOverflow) {
  PSXMemory memory{};
  R3000A cpu(&memory);

  cpu.instruction = 0x00221820;  // ADD r3, r1, r2
  cpu.registers.set(1, 0x7fffffff);
  cpu.registers.set(2, 0x10);
  cpu.registers.set(3, 0);

  cpu.dispatch();

  EXPECT_EQ(cpu.registers.get(3), 0);
  EXPECT_EQ(cpu.registers.pc, 0x80000080);
}

TEST(OpCodes, ADDUnderflow) {
  PSXMemory memory{};
  R3000A cpu(&memory);

  cpu.instruction = 0x00221820;  // ADD r3, r1, r2
  cpu.registers.set(1, 0x80000000);
  cpu.registers.set(2, 0xfffffffd);
  cpu.registers.set(3, 0);

  cpu.dispatch();

  EXPECT_EQ(cpu.registers.get(3), 0);
  EXPECT_EQ(cpu.registers.pc, 0x80000080);
}

TEST(OpCodes, ADDNegPos) {
  PSXMemory memory{};
  R3000A cpu(&memory);

  cpu.instruction = 0x00221820;  // ADD r3, r1, r2
  cpu.registers.set(1, 0x80000000);
  cpu.registers.set(2, 0x1);
  cpu.registers.set(3, 0);

  cpu.dispatch();

  EXPECT_EQ(cpu.registers.get(3), 0x80000001);
}

TEST(OpCodes, ADDPosPos) {
  PSXMemory memory{};
  R3000A cpu(&memory);

  cpu.instruction = 0x00221820;  // ADD r3, r1, r2
  cpu.registers.set(1, 0x100);
  cpu.registers.set(2, 0x200);
  cpu.registers.set(3, 0);

  cpu.dispatch();

  EXPECT_EQ(cpu.registers.get(1), 0x100);
  EXPECT_EQ(cpu.registers.get(2), 0x200);
  EXPECT_EQ(cpu.registers.get(3), 0x300);
}
