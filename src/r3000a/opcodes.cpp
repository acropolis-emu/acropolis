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

#include "cpu.h"

R3000A::opcode_handler R3000A::opcode_handlers[64] = {
    /* 00 */ nullptr,          &R3000A::op_bxx,   &R3000A::op_j,    &R3000A::op_jal,
    /* 04 */ &R3000A::op_beq,  &R3000A::op_bne,   &R3000A::op_blez, &R3000A::op_bgtz,
    /* 08 */ &R3000A::op_addi, &R3000A::op_addiu, &R3000A::op_slti, &R3000A::op_sltiu,
    /* 0c */ &R3000A::op_andi, &R3000A::op_ori,   &R3000A::op_xori, &R3000A::op_lui,
    /* 10 */ &R3000A::op_cop0, &R3000A::op_cop1,  &R3000A::op_cop2, &R3000A::op_cop3,
    /* 04 */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 08 */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 0c */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 20 */ &R3000A::op_lb,   &R3000A::op_lh,    &R3000A::op_lwl,  &R3000A::op_lw,
    /* 24 */ &R3000A::op_lbu,  &R3000A::op_lhu,   &R3000A::op_lwr,  &R3000A::op_res,
    /* 28 */ &R3000A::op_sb,   &R3000A::op_sh,    &R3000A::op_swl,  &R3000A::op_sw,
    /* 2c */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_swr,  &R3000A::op_res,
    /* 30 */ &R3000A::op_lwc0, &R3000A::op_lwc1,  &R3000A::op_lwc2, &R3000A::op_lwc3,
    /* 34 */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 38 */ &R3000A::op_swc0, &R3000A::op_swc1,  &R3000A::op_swc2, &R3000A::op_swc3,
    /* 3c */ &R3000A::op_res,  &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res

};

R3000A::opcode_handler R3000A::opcode_handlers_special[64] = {
    /* 00 */ &R3000A::op_sll,     &R3000A::op_res,   &R3000A::op_srl,  &R3000A::op_sra,
    /* 04 */ &R3000A::op_sllv,    &R3000A::op_res,   &R3000A::op_srlv, &R3000A::op_srav,
    /* 08 */ &R3000A::op_jr,      &R3000A::op_jalr,  &R3000A::op_res,  &R3000A::op_res,
    /* 0c */ &R3000A::op_syscall, &R3000A::op_break, &R3000A::op_res,  &R3000A::op_res,
    /* 10 */ &R3000A::op_mfhi,    &R3000A::op_mthi,  &R3000A::op_mflo, &R3000A::op_mtlo,
    /* 04 */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 08 */ &R3000A::op_mult,    &R3000A::op_multu, &R3000A::op_div,  &R3000A::op_divu,
    /* 0c */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 20 */ &R3000A::op_add,     &R3000A::op_addu,  &R3000A::op_sub,  &R3000A::op_subu,
    /* 24 */ &R3000A::op_and,     &R3000A::op_or,    &R3000A::op_xor,  &R3000A::op_nor,
    /* 28 */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_slt,  &R3000A::op_sltu,
    /* 2c */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 30 */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 34 */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 38 */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res,
    /* 3c */ &R3000A::op_res,     &R3000A::op_res,   &R3000A::op_res,  &R3000A::op_res
};


void R3000A::op_res() {
  exception(R3000A::RI);
}

void R3000A::op_add() {
  auto a = get_rs();
  auto b = get_rt();
  auto r = a + b;
  if (overflow(a, b, r)) {
    exception(R3000A::OVF);
  } else {
    set_rd(r);
  }
}

void R3000A::op_addi() {

}

void R3000A::op_addiu() {

}

void R3000A::op_addu() {
  auto r = get_rs() + get_rt();
  printf("ADDU: %d + %d = %d\n", get_rs(), get_rt(), r);
  set_rd(r);
}

void R3000A::op_and() {

}

void R3000A::op_andi() {

}

void R3000A::op_beq() {

}

void R3000A::op_bgtz() {

}

void R3000A::op_blez() {

}

void R3000A::op_bne() {

}

void R3000A::op_break() {

}

void R3000A::op_bxx() {

}

void R3000A::op_cop0() {

}

void R3000A::op_cop1() {

}

void R3000A::op_cop2() {

}

void R3000A::op_cop3() {

}

void R3000A::op_div() {

}

void R3000A::op_divu() {

}

void R3000A::op_j() {

}

void R3000A::op_jal() {

}

void R3000A::op_jalr() {

}

void R3000A::op_jr() {

}

void R3000A::op_lb() {

}

void R3000A::op_lbu() {

}

void R3000A::op_lh() {

}

void R3000A::op_lhu() {

}

void R3000A::op_lui() {

}

void R3000A::op_lw() {

}

void R3000A::op_lwc0() {

}

void R3000A::op_lwc1() {

}

void R3000A::op_lwc2() {

}

void R3000A::op_lwc3() {

}

void R3000A::op_lwl() {

}

void R3000A::op_lwr() {

}

void R3000A::op_mfhi() {

}

void R3000A::op_mflo() {

}

void R3000A::op_mthi() {

}

void R3000A::op_mtlo() {

}

void R3000A::op_mult() {

}

void R3000A::op_multu() {

}

void R3000A::op_nor() {

}

void R3000A::op_or() {

}

void R3000A::op_ori() {

}

void R3000A::op_sb() {

}

void R3000A::op_sh() {

}

void R3000A::op_sll() {

}

void R3000A::op_sllv() {

}

void R3000A::op_slt() {

}

void R3000A::op_slti() {

}

void R3000A::op_sltiu() {

}

void R3000A::op_sltu() {

}

void R3000A::op_sra() {

}

void R3000A::op_srav() {

}

void R3000A::op_srl() {

}

void R3000A::op_srlv() {

}

void R3000A::op_sub() {

}

void R3000A::op_subu() {

}

void R3000A::op_sw() {

}

void R3000A::op_swc0() {

}

void R3000A::op_swc1() {

}

void R3000A::op_swc2() {

}

void R3000A::op_swc3() {

}

void R3000A::op_swl() {

}

void R3000A::op_swr() {

}

void R3000A::op_syscall() {
  exception(R3000A::SYS);
}

void R3000A::op_xor() {

}

void R3000A::op_xori() {

}
