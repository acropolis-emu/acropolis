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

void R3000A::powerOn() {
  reset();
}

void R3000A::reset() {
  registers.pc = 0;
}

void R3000A::step() {
  fetch();
  dispatch();
}

void R3000A::dispatch()  {
  auto op = opcode();
  if (op == 0) { // SPECIAL (0 opcode)
    (*this.*opcode_handlers_special[func()])();
  } else {
    (*this.*opcode_handlers[op])();
  }
}

void R3000A::exception(R3000A::ExceptionCause cause) {
  registers.pc = interrupt_vector;
}
void R3000A::fetch() {
  if (registers.pc & 0x03u) {
    return exception(R3000A::ADEL); // instruction reads must be word aligned.
  }
  registers.pc = registers.next_pc;
  registers.next_pc += 4;

  instruction = memory->load_word(registers.pc); // fetch
}

