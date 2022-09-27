#pragma once

#include <cstdint>

namespace chip8_lib {

class Registers
{
public:
  Registers();

public:
  uint8_t vx[16];

  // address are 12 bits wide
  uint16_t I;
  uint16_t pc;
};
}
