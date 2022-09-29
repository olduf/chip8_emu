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
