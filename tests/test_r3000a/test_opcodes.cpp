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

using ::testing::Return;
using ::testing::_;

class MockPSXMemory
{
public:
  MOCK_CONST_METHOD1(load_word, uint32_t(uint32_t address));
};

// ADDU Tests
TEST(OpCodes, ADDU) {
  MockPSXMemory memory{};
  R3000A<MockPSXMemory> cpu(&memory);

  constexpr uint32_t ADDU_r3_r1_r2 = 0x00221821;
  EXPECT_CALL(memory, load_word(_))
      .WillOnce(Return(ADDU_r3_r1_r2));  // ADDU r3, r1, r2

  cpu.registers.gpset(1, 0x100);
  cpu.registers.gpset(2, 0x200);
  cpu.registers.gpset(3, 0xffffffff);

  auto instruction = cpu.fetch();
  EXPECT_EQ(instruction, ADDU_r3_r1_r2);

  cpu.dispatch(instruction);
  EXPECT_EQ(cpu.registers.gpget(1), 0x100);
  EXPECT_EQ(cpu.registers.gpget(2), 0x200);
  EXPECT_EQ(cpu.registers.gpget(3), 0x300);
}

// ADD tests
TEST(OpCodes, ADDOverflow) {
  MockPSXMemory memory{};
  R3000A<MockPSXMemory> cpu(&memory);

  constexpr uint32_t ADD_r3_r1_r2 = 0x00221820;
  EXPECT_CALL(memory, load_word(_))
      .WillOnce(Return(ADD_r3_r1_r2));  // ADD r3, r1, r2

  cpu.registers.gpset(1, 0x7fffffff);
  cpu.registers.gpset(2, 0x10);
  cpu.registers.gpset(3, 0);

  auto instruction = cpu.fetch();
  EXPECT_EQ(instruction, ADD_r3_r1_r2);
  cpu.dispatch(instruction);

  EXPECT_EQ(cpu.registers.gpget(3), 0);
  EXPECT_EQ(cpu.registers.pc, 0x80000080);
}

TEST(OpCodes, ADDUnderflow) {
  MockPSXMemory memory{};
  R3000A<MockPSXMemory> cpu(&memory);

  constexpr uint32_t ADD_r3_r1_r2 = 0x00221820;
  EXPECT_CALL(memory, load_word(_))
      .WillOnce(Return(ADD_r3_r1_r2));  // ADD r3, r1, r2

  cpu.registers.gpset(1, 0x80000000);
  cpu.registers.gpset(2, 0xfffffffd);
  cpu.registers.gpset(3, 0);

  auto instruction = cpu.fetch();
  EXPECT_EQ(instruction, ADD_r3_r1_r2);
  cpu.dispatch(instruction);

  EXPECT_EQ(cpu.registers.gpget(3), 0);
  EXPECT_EQ(cpu.registers.pc, 0x80000080);
}

TEST(OpCodes, ADDNegPos) {
  MockPSXMemory memory{};
  R3000A<MockPSXMemory> cpu(&memory);

  constexpr uint32_t ADD_r3_r1_r2 = 0x00221820;
  EXPECT_CALL(memory, load_word(_))
      .WillOnce(Return(ADD_r3_r1_r2));  // ADD r3, r1, r2

  cpu.registers.gpset(1, 0x80000000);
  cpu.registers.gpset(2, 0x1);
  cpu.registers.gpset(3, 0);

  auto instruction = cpu.fetch();
  EXPECT_EQ(instruction, ADD_r3_r1_r2);
  cpu.dispatch(instruction);

  EXPECT_EQ(cpu.registers.gpget(3), 0x80000001);
}

TEST(OpCodes, ADDPosPos) {
  MockPSXMemory memory{};
  R3000A<MockPSXMemory> cpu(&memory);

  constexpr uint32_t ADD_r3_r1_r2 = 0x00221820;
  EXPECT_CALL(memory, load_word(_))
      .WillOnce(Return(ADD_r3_r1_r2));  // ADD r3, r1, r2

  cpu.registers.gpset(1, 0x100);
  cpu.registers.gpset(2, 0x200);
  cpu.registers.gpset(3, 0);

  auto instruction = cpu.fetch();
  EXPECT_EQ(instruction, ADD_r3_r1_r2);
  cpu.dispatch(instruction);

  EXPECT_EQ(cpu.registers.gpget(1), 0x100);
  EXPECT_EQ(cpu.registers.gpget(2), 0x200);
  EXPECT_EQ(cpu.registers.gpget(3), 0x300);
}
