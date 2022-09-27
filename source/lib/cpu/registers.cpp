#include "lib/cpu/registers.hpp"

namespace chip8_lib {

Registers::Registers() {
  for (int i = 0; i < 16; i++) {
    this->vx[i] = 0;
  }

  this->I = 0;
  this->pc = 0x200;
}

}

//
//   I    = 0;    // Reset index register
//   sp   = 0;    // Reset stack pointer
//
//   // Reset timers
