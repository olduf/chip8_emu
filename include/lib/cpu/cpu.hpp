#pragma once

#include <cstdint>

#include "lib/cpu/registers.hpp"
#include "lib/cpu/instruction.hpp"
#include "lib/memory/mmu.hpp"

namespace chip8_lib {

class Cpu
{
public:
  Cpu(MMU* mmu);

  void tick();

private:
  MMU* mmu;
  Registers registers;
};

}
