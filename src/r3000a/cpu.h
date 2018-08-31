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

#ifndef ACROPOLIS_NECV60_H
#define ACROPOLIS_NECV60_H

#include "registers.h"
#include "../memory.h"

class R3000A {
private:
  Registers registers;
  std::shared_ptr<PSXMemory> memory;
public:
  R3000A(const R3000A&) = delete;
  R3000A& operator=(const R3000A&) = delete;
  explicit R3000A(PSXMemory *memory);

};

#endif // ACROPOLIS_NECV60_H
