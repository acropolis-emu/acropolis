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

#include <cstdint>

struct Registers {
  Registers() {}
  /*
   * Program Register Set
   */

  uint32_t r0 = 0;
  uint32_t r1 = 0;
  uint32_t r2 = 0;
  uint32_t r3 = 0;
  uint32_t r4 = 0;
  uint32_t r5 = 0;
  uint32_t r6 = 0;
  uint32_t r7 = 0;
  uint32_t r8 = 0;
  uint32_t r9 = 0;
  uint32_t r10 = 0;
  uint32_t r11 = 0;
  uint32_t r12 = 0;
  uint32_t r13 = 0;
  uint32_t r14 = 0;
  uint32_t r15 = 0;
  uint32_t r16 = 0;
  uint32_t r17 = 0;
  uint32_t r18 = 0;
  uint32_t r19 = 0;
  uint32_t r20 = 0;
  uint32_t r21 = 0;
  uint32_t r22 = 0;
  uint32_t r23 = 0;
  uint32_t r24 = 0;
  uint32_t r25 = 0;
  uint32_t r26 = 0;
  uint32_t r27 = 0;
  uint32_t r28 = 0;
  uint32_t r29 = 0;  // argument pointer alias
  uint32_t r30 = 0;  // frame pointer alias
  uint32_t r31 = 0;  // stack pointer alias

  uint32_t &ap = r29;  // argument pointer
  uint32_t &fp = r30;  // frame pointer
  uint32_t &sp = r31;  // stack pointer

  uint32_t pc = 0;   // program counter

  struct psw_t {
    union {
      uint32_t value = 0;
      struct {
        // integer flags
        uint8_t z : 1;      // integer zero flag
        uint8_t s : 1;      // integer sign flag
        uint8_t oc : 1;     // integer overflow flag
        uint8_t cy : 1;     // integer carry flag
        uint8_t : 4;        // reserved

        // float flags
        uint8_t fpr : 1;    // float precision flag
        uint8_t fud : 1;    // float underflow
        uint8_t fov : 1;    // float overflow
        uint8_t fzd : 1;    // float zero divide
        uint8_t fiv : 1;    // invalid float operation
        uint8_t : 3;        // reserved

        // NB: upper half word is protected
        // processor control
        uint8_t te : 1;     // trace enable
        uint8_t ae : 1;     // address trap enable
        uint8_t ie : 1;     // interrupt enable
        uint8_t : 5;        // reserved

        // status
        uint8_t el : 2;     // execution level
        uint8_t ip : 1;     // instruction pending
        uint8_t tp : 1;     // trace pending
        uint8_t is : 1;     // interrupt stack
        uint8_t em : 1;     // emulation mode
        uint8_t ata : 1;    // asynchronous task trap active
        uint8_t asa : 1;    // asynchronous system trap active
      };
    };

    explicit operator uint32_t &() { return value; }
    explicit operator uint32_t const () { return value; }

  } psw;

  /*
   * Privileged Register Set
   */

  uint32_t l0sp = 0;  // level 0 stack pointer
  uint32_t l1sp = 0;  // level 1 stack pointer
  uint32_t l2sp = 0;  // level 2 stack pointer
  uint32_t l3sp = 0;  // level 3 stack pointer
  uint32_t isp = 0;   // interrupt stack pointer

  uint32_t sbp = 0;   // system base pointer

  struct sycw_t {
    union {
      uint32_t value = 0;
      struct {
        uint8_t vm : 1;     // virtual mode

        uint8_t : 3;        // reserved

        uint8_t ast : 3;    // asynchronous system trap level

        uint8_t : 1;        // reserved

        uint8_t spsi : 4;   // stack point switching inhibited
        uint8_t atrsi : 4;  // area table register switching inhibited
      };
    };
  } sycw;  // system control word

  uint32_t tr = 0;    // task register ([31:2] tcbb, [1:0] 0)

  struct tkcw_t {  // task control word
    union {
      uint32_t value = 0;
      struct {
        uint8_t rd : 2;   // float rounding control
        uint8_t rdi : 1;  // integer rounding control

        uint8_t : 1;      // reserved

        uint8_t fpt : 1;  // floating point precision trap enable
        uint8_t fut : 1;  // floating point underflow trap enable
        uint8_t fvt : 1;  // floating point overflow trap enable
        uint8_t fzt : 1;  // floating point zero divide trap enable
        uint8_t fit : 1;  // floating point invalid operation trap enable

        uint8_t otm : 1;  // operand trap mask

        uint8_t : 3;      // reserved

        uint8_t att : 3;  // asynchronous task trap level
      };
    };

    explicit operator uint32_t &() { return value; }
    explicit operator uint32_t const () { return value; }
  } tkcw;

  const uint32_t pir = 0x0600;   // processor ID register

  struct atbr_t {
    union {
      uint32_t value = 0;
      struct {
        uint8_t v : 1;      // valid
        uint8_t d : 1;      // direction
        uint8_t : 1;        // reserved
        uint32_t atb : 21;  // 3-lsb set to 0
      };
    };

    explicit operator uint32_t &() { return value; }
    explicit operator uint32_t const () { return value; }
  };

  struct atlr_t {
    union {
      uint32_t value = 0;
      struct {
        uint8_t : 1;        // reserved
        uint16_t los : 10;  // limit of section
        uint8_t : 1;        // reserved
      };
    };

    explicit operator uint32_t &() { return value; }
    explicit operator uint32_t const () { return value; }
  };

  atbr_t atbr0;  // area table base register 0
  atlr_t atlr0;  // area table length register 0
  atbr_t atbr1;  // area table base register 1
  atlr_t atlr1;  // area table length register 1
  atbr_t atbr2;  // area table base register 2
  atlr_t atlr2;  // area table length register 2
  atbr_t atbr3;  // area table base register 3
  atlr_t atlr3;  // area table length register 3

  struct trmod_t {
    union {
      uint32_t value = 0;
      struct {
        uint8_t : 1;      // reserved

        uint8_t w0 : 1;   // adtr0 write
        uint8_t r0 : 1;   // adtr0 read
        uint8_t e0 : 1;   // adtr0 execute

        uint8_t : 5;      // reserved

        uint8_t w1 : 1;   // adtr1 write
        uint8_t r1 : 1;   // adtr1 read
        uint8_t e1 : 1;   // adtr1 execute
      };
    };

    explicit operator uint32_t &() { return value; }
    explicit operator uint32_t const () { return value; }
  } trmod;  // trap mode register

  uint32_t adtr0 = 0;   // address trap register 0
  uint32_t adtmr0 = 0;  // address trap mask register 0
  uint32_t adtr1 = 0;   // address trap register 1
  uint32_t adtmr1 = 0;  // address trap mask register 1

  uint32_t psw2 = 0;  // program status word 2 (for v20/v30 emulation)
};

#endif //ACROPOLIS_REGISTERS_H
