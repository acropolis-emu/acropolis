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

#include "memory.h"

uint8_t PSXMemory::load_byte(uint32_t address) {
  return 0;
}

uint16_t PSXMemory::load_halfword(uint32_t address) {
  return 0;
}

uint32_t PSXMemory::load_word(uint32_t address) {
  return 0;
}

void PSXMemory::store_byte(uint32_t address, uint8_t data) {

}

void PSXMemory::store_halfword(uint32_t address, uint16_t data) {

}

void PSXMemory::store_word(uint32_t address, uint32_t data) {

}

void PSXMemory::load_bios(std::array<uint8_t, BIOS_SIZE> bios) {
  this->bios = bios;
}
