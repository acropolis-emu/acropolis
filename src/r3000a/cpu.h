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

class R3000A {
public:
  typedef void (R3000A:: *opcode_handler)();

  static constexpr uint32_t interrupt_vector = 0x80000080u;

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

  PSXMemory *memory;
  static opcode_handler opcode_handlers[64];
  static opcode_handler opcode_handlers_special[64];
  Registers registers;
  uint32_t instruction; // current instruction

  R3000A(const R3000A&) = delete;
  R3000A& operator=(const R3000A&) = delete;
  explicit R3000A(PSXMemory *memory) {
    this->memory = memory;
  }

  void powerOn();
  void reset();

  // execute the cpu
  void step();
  void dispatch();
  void exception(ExceptionCause cause);

  // Opcodes
  void op_res();  // asserts reserved instruction exception
  void op_add();
  void op_addi();
  void op_addiu();
  void op_addu();
  void op_and();
  void op_andi();
  void op_beq();
  void op_bgtz();
  void op_blez();
  void op_bne();
  void op_break();
  void op_bxx();
  void op_cop0();
  void op_cop1();
  void op_cop2();
  void op_cop3();
  void op_div();
  void op_divu();
  void op_j();
  void op_jal();
  void op_jalr();
  void op_jr();
  void op_lb();
  void op_lbu();
  void op_lh();
  void op_lhu();
  void op_lui();
  void op_lw();
  void op_lwc0();
  void op_lwc1();
  void op_lwc2();
  void op_lwc3();
  void op_lwl();
  void op_lwr();
  void op_mfhi();
  void op_mflo();
  void op_mthi();
  void op_mtlo();
  void op_mult();
  void op_multu();
  void op_nor();
  void op_or();
  void op_ori();
  void op_sb();
  void op_sh();
  void op_sll();
  void op_sllv();
  void op_slt();
  void op_slti();
  void op_sltiu();
  void op_sltu();
  void op_sra();
  void op_srav();
  void op_srl();
  void op_srlv();
  void op_sub();
  void op_subu();
  void op_sw();
  void op_swc0();
  void op_swc1();
  void op_swc2();
  void op_swc3();
  void op_swl();
  void op_swr();
  void op_syscall();
  void op_xor();
  void op_xori();

  constexpr bool overflow(uint32_t a, uint32_t b, uint32_t r) {
    return (~(a ^ b) & (a ^ r) & 0x80000000u) > 0;
  }

  constexpr uint32_t decode_opcode() {
    return (instruction & 0xfc000000u) >> 26u;
  }

  constexpr uint32_t decode_rs() {
    return (instruction & 0x3e00000u) >> 21u;
  }

  constexpr uint32_t decode_rt() {
    return (instruction & 0x1f0000u) >> 16u;
  }

  constexpr uint32_t decode_rd() {
    return (instruction & 0xf800u) >> 11u;
  }

  constexpr uint32_t decode_shamt() {
    return (instruction & 0x7c0u) >> 6u;
  }

  constexpr uint32_t decode_func() {
    return instruction & 0x3fu;
  }

  constexpr uint32_t decode_target() {
    return instruction & 0x3ffffffu;
  }

  constexpr uint32_t decode_immediate() {
    return instruction & 0xffffu;
  }

  constexpr uint32_t rt() {
    return registers.get(decode_rt());
  }

  constexpr void rt(uint32_t v) {
    registers.set(decode_rt(), v);
  }

  constexpr uint32_t rs() {
    return registers.get(decode_rs());
  }

  constexpr void rs(uint32_t v) {
    registers.set(decode_rs(), v);
  }

  constexpr uint32_t rd() {
    return registers.get(decode_rd());
  }

  constexpr void rd(uint32_t v) {
    registers.set(decode_rd(), v);
  }


};

#endif // ACROPOLIS_R3000A_H
