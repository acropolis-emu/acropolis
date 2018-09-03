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

#ifndef ACROPOLIS_R3000A_H
#define ACROPOLIS_R3000A_H

#include "registers.h"
#include "../memory.h"

template <class M>
class R3000A {
private:
  M *memory;
public:
  Registers registers;

  R3000A(const R3000A&) = delete;
  R3000A& operator=(const R3000A&) = delete;
  explicit R3000A(M *memory) {
    this->memory = memory;
  }

  // execute the cpu
  void main() {
    auto instruction = fetch();
    dispatch(instruction);
  }

  constexpr void dispatch(uint32_t instruction) {
    switch (decode_opcode(instruction)) {
    case 0: // SPECIAL (0 opcode)
      dispatch_special(instruction);
      break;
    default:
      // exception
      break;
    }
  }

  constexpr void dispatch_special(uint32_t instruction) {
    uint32_t temp = 0;
    switch (decode_rtype_func(instruction)) {
    case 0x21:  // ADDU
      temp = registers.gpget(decode_rtype_rs(instruction)) + registers.gpget(decode_rtype_rt(instruction));
      registers.gpset(decode_rtype_rd(instruction), temp);
      break;
    default:
      // exception
      break;
    }
  }

  constexpr uint32_t fetch() {
    return memory->load_word(registers.pc);
  }

  constexpr uint32_t decode_opcode(uint32_t instruction) {
    return (instruction & 0xfc000000u) >> 26u;
  }

  constexpr uint32_t decode_rtype_rt(uint32_t instruction) {
    return (instruction & 0x1f0000u) >> 16u;
  }

  constexpr uint32_t decode_rtype_rs(uint32_t instruction) {
    return (instruction & 0x3e00000u) >> 21u;
  }

  constexpr uint32_t decode_rtype_rd(uint32_t instruction) {
    return (instruction & 0xf800u) >> 11u;
  }

  constexpr uint32_t decode_rtype_sa(uint32_t instruction) {
    return (instruction & 0x7c0u) >> 6u;
  }

  constexpr uint32_t decode_rtype_func(uint32_t instruction) {
    return instruction & 0x3fu;
  }

};

#endif // ACROPOLIS_R3000A_H
