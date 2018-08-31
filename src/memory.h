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

#ifndef ACROPOLIS_MEMORY_H
#define ACROPOLIS_MEMORY_H

#include <array>
#include <cstddef>
#include <cstdint>

/*
 * Representation of the memory in the PSX
 *
 * 2MB of RAM
 *
 *  Address Range          | Function
 *  -------------          | --------
 *  0x00000000  0x0000ffff | Kernel (64K)
 *  0x00010000  0x001fffff | User Memory (1.9 Meg)
 *  0x1f000000  0x1f00ffff | Parallel Port (64K)
 *  0x1f800000  0x1f8003ff | Scratch Pad (1024 bytes)
 *  0x1f801000  0x1f802fff | Hardware Registers (8K)
 *  0x80000000  0x801fffff | Kernel and User Memory Mirror (2 Meg) Cached
 *  0xa0000000  0xa01fffff | Kernel and User Memory Mirror (2 Meg) Uncached
 *  0xbfc00000  0xbfc7ffff | BIOS (512K)
 *
 */
constexpr size_t BIOS_SIZE = 0x80000;

class PSXMemory {
private:
  std::array<uint8_t, 0x10000> main{};  // kernel and user memory
  std::array<uint8_t, 0x10000> parallel_port{};
  std::array<uint8_t, 0x400> scratch{};
  std::array<uint8_t, BIOS_SIZE> bios{};
public:
  PSXMemory() = default;
  PSXMemory(const PSXMemory&) = delete;
  PSXMemory& operator=(const PSXMemory&) = delete;

  uint8_t load_byte(uint32_t address);
  uint16_t load_halfword(uint32_t address);
  uint32_t load_word(uint32_t address);

  void store_byte(uint32_t address, uint8_t data);
  void store_halfword(uint32_t address, uint16_t data);
  void store_word(uint32_t address, uint32_t data) ;

  void load_bios(std::array<uint8_t, BIOS_SIZE> bios);
};

#endif //ACROPOLIS_MEMORY_H
