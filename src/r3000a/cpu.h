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
  static constexpr uint32_t interrupt_vector = 0x80000080u;
  static constexpr uint32_t max_int_2s = 0x7fffffffu;

  enum ExceptionCause {
    INT,  // External interrupt
    MOD,  // TLB modification exception
    TLBL, // TLB miss exception (load or instruction fetch)
    TLBS, // TLB miss exception (store)
    ADEL, // Address error exception (load or instruction fetch)
    ADES, // Address error exception (store)
    IBE,  // Bus error exception (instruction fetch)
    DBE,  // Bus error exception (data load or store)
    SYS,  // SYSCALL exception
    BP,   // Breakpoint exception
    RI,   // Reserved instruction exception
    CPU,  // Co-processor unavailable exception
    OVF   // Arithmetic overflow exception
    // reserved
  };

public:
  Registers registers;

  R3000A(const R3000A&) = delete;
  R3000A& operator=(const R3000A&) = delete;
  explicit R3000A(M *memory) {
    this->memory = memory;
  }

  // execute the cpu
  void step() {
    auto instruction = fetch();
    dispatch(instruction);
  }

  constexpr uint64_t dispatch(uint32_t instruction) {
    switch (decode_opcode(instruction)) {
    case 0: // SPECIAL (0 opcode)
      return dispatch_alu_instruction(instruction);
    default:
      exception(RI);
      break;
    }
    return 0;
  }

  void exception(ExceptionCause cause) {
    registers.pc = interrupt_vector;
  }

  constexpr uint64_t dispatch_alu_instruction(uint32_t instruction) {
    uint32_t temp32 = 0;
    uint64_t temp64 = 0;
    auto rs = decode_rtype_rs(instruction);
    auto rt = decode_rtype_rt(instruction);
    auto rd = decode_rtype_rd(instruction);
    auto shamt = decode_rtype_shamt(instruction);
    auto funct = decode_rtype_func(instruction);

    switch (funct) {
    case 0x20:  // ADD (can throw overflow exception)
      temp32 = registers.gpget(rs) + registers.gpget(rt);

      // positive + positive = negative, overflow
      // negative + negative = positive, underflow
      if ((!is_neg_2s(registers.gpget(rs)) and !is_neg_2s(registers.gpget(rt)) and is_neg_2s(temp32))
          or (is_neg_2s(registers.gpget(rs)) and is_neg_2s(registers.gpget(rt)) and !is_neg_2s(temp32))) {
        exception(OVF);
      } else {
        registers.gpset(rd, temp32);
      }
      break;
    case 0x21:  // ADDU
      registers.gpset(rd, registers.gpget(rs) + registers.gpget(rt));
      break;
    default:
      // exception
      break;
    }
    return 0;
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

  constexpr uint32_t decode_rtype_shamt(uint32_t instruction) {
    return (instruction & 0x7c0u) >> 6u;
  }

  constexpr uint32_t decode_rtype_func(uint32_t instruction) {
    return instruction & 0x3fu;
  }

  constexpr bool is_neg_2s(uint32_t operand) {
    return (operand > max_int_2s);
  }

};

#endif // ACROPOLIS_R3000A_H
