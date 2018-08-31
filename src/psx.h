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

#ifndef ACROPOLIS_PSX_H
#define ACROPOLIS_PSX_H

#include <cstdint>
#include "memory.h"
#include "r3000a/cpu.h"

class PSX {
  PSXMemory memory;
  std::unique_ptr<R3000A> cpu;

  PSX();
};

#endif //ACROPOLIS_PSX_H
