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

#ifndef ACROPOLIS_REGISTERS_H
#define ACROPOLIS_REGISTERS_H

#include <cstdlib>
#include <cstdint>
#include <utility>

class Registers {
private:
  uint32_t regs[32]{0};
  uint32_t next_pc = 0;           // next PC (see pc)

public:
  Registers() = default;

  /*
   * Get a reference for a general purpose register
   */
  constexpr uint32_t get(size_t reg) noexcept {
    return regs[reg];
  }

  constexpr void set(size_t reg, uint32_t v) noexcept {
    if (reg > 0) {
      regs[reg] = v;
    }
  }

  /*
   * Copies the value of src register to the destination register (src -> dst)
   */
  constexpr void copy(size_t src, size_t dst) noexcept {
    if (dst > 0) {  // do nothing on copy to r0
      regs[dst] = regs[src];
    }
  }

  /*
   * Swap two general purpose registers (src <-> dst)
   */
  constexpr void swap(size_t src, size_t dst) noexcept {
    if (dst > 0) {  // swap if the destination is not r0
      std::swap(regs[src], regs[dst]);
    } else { // if the dst is r0 then just copy 0 to the rs
      copy(src, 0);
    }
  }

  /*
   * Sign extend a 16 bit value register to 32 bits
   */
  constexpr void sign_extend_16(size_t index) noexcept {
    if (index > 0 && regs[index] & 0x8000) {
      regs[index] |= 0xFFFF0000;
    }
  }

  constexpr void increment_pc(int32_t offset) {
    pc = next_pc;       // update the PC to the next value
    next_pc += offset;  // update the next PC value (could be modified later by the instruction)
  }

  /* Registers */
  uint32_t hi = 0;                // multiplication registers
  uint32_t lo = 0;
  uint32_t pc = 0;                // programme counter

  /* aliases */
  const uint32_t zr = 0;
  uint32_t &at = regs[1];         // reserved for the compiler

  uint32_t &v0 = regs[2];         // values
  uint32_t &v1 = regs[3];

  uint32_t &a0 = regs[4];         // arguments
  uint32_t &a1 = regs[5];
  uint32_t &a2 = regs[6];
  uint32_t &a3 = regs[7];

  uint32_t &t0 = regs[8];         // temps
  uint32_t &t1 = regs[9];
  uint32_t &t2 = regs[10];
  uint32_t &t3 = regs[11];
  uint32_t &t4 = regs[12];
  uint32_t &t5 = regs[13];
  uint32_t &t6 = regs[14];
  uint32_t &t7 = regs[15];

  uint32_t &s0 = regs[16];         // saved
  uint32_t &s1 = regs[17];
  uint32_t &s2 = regs[18];
  uint32_t &s3 = regs[19];
  uint32_t &s4 = regs[20];
  uint32_t &s5 = regs[21];
  uint32_t &s6 = regs[22];
  uint32_t &s7 = regs[23];

  uint32_t &t8 = regs[24];         // more temps
  uint32_t &t9 = regs[25];

  uint32_t &k0 = regs[26];         // kernel reserved
  uint32_t &k1 = regs[27];

  uint32_t &gp = regs[28];         // global pointer
  uint32_t &sp = regs[29];         // stack pointer
  uint32_t &fp = regs[30];         // frame pointer
  uint32_t &ra = regs[31];         // return address

};

#endif //ACROPOLIS_REGISTERS_H
